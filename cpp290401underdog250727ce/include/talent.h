#pragma once
#include "common.h"

class Talent {
  public:
    Talent() = default ;
    virtual ~Talent() {};

    virtual std::string getTalent() = 0;
};

class Barking : public Talent{
  public:
    Barking() = default;
    ~Barking() override {}

    std::string getTalent() override;
};

class Running : public Talent{
  public:
    Running() = default;
    ~Running() override {}

    std::string getTalent() override;
};

class Swimming : public Talent {
  public:
    Swimming() = default;
    ~Swimming() override {}

    std::string getTalent() override;
};

class Dancing : public Talent {
  public:
    Dancing() = default;
    ~Dancing() override {}

    std::string getTalent() override;
};

class Counting : public Talent {
  public:
    Counting() = default;
    ~Counting() override {}

    std::string getTalent() override;
};