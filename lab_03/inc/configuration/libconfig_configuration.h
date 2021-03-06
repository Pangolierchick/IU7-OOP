#pragma once

#include <iostream>
#include <memory>

#include "/usr/local/include/libconfig.h++"

#include "abstract_configuration.h"
#include "abstract_drawer.h"

#define DEFAULT_FILE "driver.cfg"

class LibconfConfiguration : public AbstractConfiguration {
public:
    explicit LibconfConfiguration(std::shared_ptr<std::string>& source);

    void read_configuration(std::shared_ptr<std::string> source = nullptr) override;

    AbstractConfiguration::frames get_frame() override;

    AbstractConfiguration::sources get_load_source() override;

private:
    std::shared_ptr<libconfig::Config> cfg;
};
