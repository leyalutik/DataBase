#pragma once

#include "Tests.h"
#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"


using namespace std;

void Test_Database();
void Test_ParseDate();
void Test_EventDate();
void Test_ComparisonDate();

void Test_Last();

void TestParseCondition();
void TestParseEvent();
