#pragma once
#include <memory>

class Application {
public: 
    Application();
    ~Application();

    void run();
private:
    class Impl;
    std::unique_ptr<Impl> m_d;
};