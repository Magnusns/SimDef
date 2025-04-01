#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_STL_

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

#include <iostream>
#include <set>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>
#include <ctime>

using websocketpp::connection_hdl;
using json = nlohmann::json;
typedef websocketpp::server<websocketpp::config::asio> server;

struct Objekt {
    int id;
    double x;
    double y;
    double hastighet;
    double retning;
};

class SensorSimulator {
private:
    std::vector<Objekt> objekter;
    int nesteID = 1;
    std::set<connection_hdl, std::owner_less<connection_hdl>> tilkoblinger;
    server ws_server;

    std::string vurderTrussel(const Objekt& obj) {
        double dist = std::sqrt(obj.x * obj.x + obj.y * obj.y);
        if (obj.hastighet > 4.5 && dist < 50) {
            return "trussel";
        } else if (obj.hastighet > 4.5) {
            return "mistenkelig";
        }
        return "normal";
    }

    void loggTrussel(const Objekt& obj, const std::string& status) {
        if (status == "normal") return;

        std::ofstream fil("../data/trusler.log", std::ios::app);
        if (!fil.is_open()) return;

        std::time_t nå = std::time(nullptr);
        char tidStr[20];
        std::strftime(tidStr, sizeof(tidStr), "%Y-%m-%d %H:%M:%S", std::localtime(&nå));

        fil << tidStr
            << " | ID " << obj.id
            << " | " << status
            << " | x=" << obj.x
            << " y=" << obj.y
            << " | hastighet=" << obj.hastighet
            << "\n";

        fil.close();
    }

public:
    SensorSimulator() {
        ws_server.init_asio();
        ws_server.set_open_handler([this](connection_hdl hdl) {
            tilkoblinger.insert(hdl);
        });
        ws_server.set_close_handler([this](connection_hdl hdl) {
            tilkoblinger.erase(hdl);
        });
    }

    void startServer() {
        ws_server.set_message_handler([](connection_hdl, server::message_ptr) {});
        ws_server.listen(9002);
        ws_server.start_accept();
        std::thread([this]() {
            ws_server.run();
        }).detach();
    }

    void opprettObjekter(int antall) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> pos(0, 100);
        std::uniform_real_distribution<> hast(1, 6);
        std::uniform_real_distribution<> vinkel(0, 360);

        for (int i = 0; i < antall; ++i) {
            Objekt obj {
                nesteID++,
                pos(gen), pos(gen),
                hast(gen),
                vinkel(gen)
            };
            objekter.push_back(obj);
        }
    }

    void simulerBevegelse(int sekunder) {
        for (int t = 0; t < sekunder; ++t) {
            json data = json::array();
            for (auto& obj : objekter) {
                double rad = obj.retning * M_PI / 180.0;
                obj.x += cos(rad) * obj.hastighet;
                obj.y += sin(rad) * obj.hastighet;

                std::string status = vurderTrussel(obj);
                loggTrussel(obj, status);

                data.push_back({
                    {"id", obj.id},
                    {"x", obj.x},
                    {"y", obj.y},
                    {"hastighet", obj.hastighet},
                    {"retning", obj.retning},
                    {"status", status}
                });
            }

            std::string json_data = data.dump();

            for (auto it = tilkoblinger.begin(); it != tilkoblinger.end(); ) {
                try {
                    ws_server.send(*it, json_data, websocketpp::frame::opcode::text);
                    ++it;
                } catch (const websocketpp::exception& e) {
                    std::cerr << "Feil ved sending: " << e.what() << std::endl;
                    it = tilkoblinger.erase(it);
                }
            }

            std::cout << "Sendte data: " << json_data << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

int main() {
    SensorSimulator simulator;
    simulator.startServer();
    simulator.opprettObjekter(3);
    simulator.simulerBevegelse(30);
    return 0;
}