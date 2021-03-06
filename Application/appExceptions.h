#ifndef APP_EXCEPTIONS_HEADER
#define APP_EXCEPTIONS_HEADER

#include <exception>
#include <string>

class AppException: public std::exception {
protected:
    std::string message{};
public:
    const char* what() const noexcept;
};

class ListExistsException: public AppException
{
private:
    std::string listName;
public:
    ListExistsException(std::string const& name);
};

class NoListSelectedException: public AppException
{
public:
    NoListSelectedException();
};

class BadProductException: public AppException
{
private:
    std::string productName;
public:
    BadProductException(std::string const& name);
};

class BadListException: public AppException
{
private:
    std::string listName;
public:
    BadListException(std::string const& name);
};

class BadCountException: public AppException
{
public:
    BadCountException(bool tooLarge);
};

class ProductNotOnListException: public AppException
{
private:
    std::string productName;
    std::string listName;
public:
    ProductNotOnListException(std::string const& lName, std::string const& prodName);
};

class NotEnoughArgsException: public AppException
{
private:
    int provided;
    int needed;
public:
    NotEnoughArgsException(int takes, int got);
};

#endif