#include <facade/facade.h>

void Facade::execute(BaseCommand& command) {
    command.execute();
}
