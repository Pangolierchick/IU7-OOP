#include <configuration/configuration_creator.h>

#include <configuration/libconfig_configuration.h>

std::shared_ptr<AbstractConfiguration> ConfigurationCreator::get_configuration(std::shared_ptr<std::string> source) {
    if (_conf == nullptr)
        create_instance(source);
    else if (source)
        _conf->read_configuration(source);

    return _conf;
}

void ConfigurationCreator::create_instance(std::shared_ptr<std::string> &source) {
    static std::shared_ptr<AbstractConfiguration> conf(new LibconfConfiguration(source));

    _conf = conf;
}


