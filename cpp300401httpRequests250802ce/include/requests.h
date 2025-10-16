#pragma once
#include "common.h"
#include "loclib.h"

class Request {
  public:
    Request() = default;
    virtual ~Request() {};
    virtual void response() = 0;
    virtual void response(std::string&, std::string&) {};
};

class RequestGet : public Request {
  public:
    RequestGet() = default;
    ~RequestGet() override {};
    void response() override;
    void response(std::string&, std::string&) override;
};

class RequestPut : public Request {
  public:
    RequestPut() = default;
    ~RequestPut() override {};
    void response() override;
};

class RequestDelete : public Request {
  public:
    RequestDelete() = default;
    ~RequestDelete() override {};
    void response() override;
};

class RequestPatch : public Request {
  public:
    RequestPatch() = default;
    ~RequestPatch() override {};
    void response() override;
};

class RequestPost : public Request {
  public:
    RequestPost() = default;
    ~RequestPost() override {};
    void response() override;
};

class RequestHead : public Request {
  public:
    RequestHead() = default;
    ~RequestHead() override {};
    void response() override;
};

