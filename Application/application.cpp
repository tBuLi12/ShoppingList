#include "application.h"
#include "interface.h"
#include "listExceptions.h"
#include <memory>
#include <iostream>
#define DEFINE_CMD(name) void Application::name::exec(std::vector<std::string> args) 

DEFINE_CMD(NewList) {
    if (args.size() < 1) {
        throw NotEnoughArgsException(1, args.size());
    }
    if (caller->lists.find(args[0]) != caller->lists.end()) {
        throw ListExistsException(args[0]);
    }
    caller->lists[args[0]] = new List(args[0]);
    caller->selected = caller->lists[args[0]];
    std::cout << "List " << args[0] << " created." << std::endl;
}

DEFINE_CMD(DeleteList) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    caller->lists.erase(caller->selected->get_list_name());
    std::cout << "List " << caller->selected->get_list_name() << " deleted." << std::endl;
    delete caller->selected;
    caller->selected = nullptr;
}

DEFINE_CMD(Add) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    if (args.size() < 1) {
        throw NotEnoughArgsException(1, args.size());
    }
    auto product = caller->products.find(args[0]);
    if (product == caller->products.end()) {
        throw BadProductException(args[0]);
    }
    if (args.size() > 1) {
        int count = std::stoi(args[1]);
        caller->selected->add_product(product->second, count);
        std::cout << args[1] << '*' << args[0] << " added." << std::endl;
    } else {
        caller->selected->add_product(product->second);
        std::cout << args[0] << " added." << std::endl;
    }
}

DEFINE_CMD(Remove) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    if (args.size() < 1) {
        throw NotEnoughArgsException(1, args.size());
    }
    auto product = caller->products.find(args[0]);
    if (product == caller->products.end()) {
        throw BadProductException(args[0]);
    }
    //caller->selected->delete_product(product->second);
    std::cout << args[0] << " removed." << std::endl;
}

DEFINE_CMD(Info) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    if (args.size() < 1) {
        throw NotEnoughArgsException(1, args.size());
    }
    auto product = caller->products.find(args[0]);
    if (product == caller->products.end()) {
        throw BadProductException(args[0]);
    }
    std::cout << product->second->get_info();
}

DEFINE_CMD(Count) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    if (args.size() < 2) {
        throw NotEnoughArgsException(2, args.size());
    }
    auto product = caller->products.find(args[0]);
    if (product == caller->products.end()) {
        throw BadProductException(args[0]);
    }
    //caller->selected->set_count(product->second, std::stoi(args[1]));
    std::cout << "Count of " << args[0] << " set to " << args[1] << std::endl;
}

Application::Application(): interface(selected) {
    #define COMMAND(name, hasArgs) interface.registerCommand(#name, std::unique_ptr<UI::Command>(new name(this)));
    #include "commands.cmds"
    #undef COMMAND
}

void Application::run() {
    interface.run();
}