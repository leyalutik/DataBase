#pragma once
#include "condition_parser.h"
#include "node.h"
#include "token.h"
#include "date.h"

#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);


void TestParseCondition();

