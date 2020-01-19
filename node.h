#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<sstream>
#include<string>
#include<utility>
#include<algorithm>
#include<memory>

#include "date.h"
using namespace std;

enum class Comparison{
Less ,
LessOrEqual,
Greater,
GreaterOrEqual,
Equal,
NotEqual
};

enum class LogicalOperation{
Or,
And
};

class Node{
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
	virtual void Print() const = 0;
};

class EmptyNode : public Node {
public:
	EmptyNode();
	void Print() const override{
		cout<<"Empty Node\n";
	}
	bool Evaluate(const Date& date, const string& event) const override{
		return true;
	}

};

class DateComparisonNode: public Node {
public:
	DateComparisonNode(const Comparison cmp,const Date& bound);
	void Print() const override{
			cout<<"DateComparisonNode \n";
			switch(DateComparisonNode::_cmp){
				case Comparison::Less :
					cout<<"cmp="<<"<"<<" "<<"bound="<<_bound<<endl;
					break;
				case Comparison::Greater :
					cout<<"cmp="<<">"<<" "<<"bound="<<_bound<<endl;
					break;
				case Comparison::GreaterOrEqual :
					cout<<"cmp="<<">="<<" "<<"bound="<<_bound<<endl;
					break;
				case Comparison::Equal :
					cout<<"cmp="<<"=="<<" "<<"bound="<<_bound<<endl;
					break;
				case Comparison::LessOrEqual :
					cout<<"cmp="<<"<="<<" "<<"bound="<<_bound<<endl;
					break;
				case Comparison::NotEqual :
					cout<<"cmp="<<"!="<<" "<<"bound="<<_bound<<endl;
					break;

				default:
					cout<<"cmp="<<"Unknown sigh"<<" "<<"bound="<<_bound<<endl;
			}
		}
	bool Evaluate(const Date& date,const string& event) const override {
			switch(DateComparisonNode::_cmp){
				case Comparison::Less :
					return date.date < DateComparisonNode::_bound;
					break;
				case Comparison::Greater :
					return date.date > DateComparisonNode::_bound;
					break;
				case Comparison::GreaterOrEqual :
					return date.date >= DateComparisonNode::_bound;
					break;
				case Comparison::Equal :
					return date.date == DateComparisonNode::_bound;
					break;
				case Comparison::LessOrEqual :
					return date.date <= DateComparisonNode::_bound;
					break;
				case Comparison::NotEqual :
					return date.date != DateComparisonNode::_bound;
					break;

				default:
					return false;
			}
		}
	const Comparison _cmp;
	const string _bound;

};

class EventComparisonNode: public Node {
public:
	EventComparisonNode( const Comparison cmp,const string& bound);
	void Print() const override{

		cout<<"EventComparisonNode Node\n";
					switch(EventComparisonNode::_cmp){
						case Comparison::Less :
							cout<<"cmp="<<"<"<<" "<<"bound="<<_bound<<endl;
							break;
						case Comparison::Greater :
							cout<<"cmp="<<">"<<" "<<"bound="<<_bound<<endl;
							break;
						case Comparison::GreaterOrEqual :
							cout<<"cmp="<<">="<<" "<<"bound="<<_bound<<endl;
							break;
						case Comparison::Equal :
							cout<<"cmp="<<"=="<<" "<<"bound="<<_bound<<endl;
							break;
						case Comparison::LessOrEqual :
							cout<<"cmp="<<"<="<<" "<<"bound="<<_bound<<endl;
							break;
						case Comparison::NotEqual :
							cout<<"cmp="<<"!="<<" "<<"bound="<<_bound<<endl;
							break;

						default:
							cout<<"cmp="<<"Unknown sigh"<<" "<<"bound="<<_bound<<endl;
					}

	}
	bool Evaluate(const Date& date,const string& event) const override{
			switch(EventComparisonNode::_cmp){
						case Comparison::Less :
							return event < EventComparisonNode::_bound;
							break;
						case Comparison::Greater :
							return event > EventComparisonNode::_bound;
							break;
						case Comparison::GreaterOrEqual :
							return event >= EventComparisonNode::_bound;
							break;
						case Comparison::Equal :
							return event == EventComparisonNode::_bound;
							break;
						case Comparison::LessOrEqual :
							return event <= EventComparisonNode::_bound;
							break;
						case Comparison::NotEqual :
							return event != EventComparisonNode::_bound;
							break;

						default:
							return false;
					}
		}

	const Comparison _cmp;
	const string _bound;

};



class LogicalOperationNode : public Node{
public:
	LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left,
			shared_ptr<Node> right);
	void Set_Left(shared_ptr<Node> left);
	void Set_Right(shared_ptr<Node> right);
	void Print() const override{
		cout<<"LogicalOperationNode\n";
	}
	bool Evaluate(const Date& date, const string& event) const override{
		switch(_op){
		case LogicalOperation::And :
			return ( _left->Evaluate(date,event) && _right->Evaluate(date,event));
			break;
		case LogicalOperation::Or :
			return ( _left->Evaluate(date,event) || _right->Evaluate(date,event));
			break;
		default :{
					cout<<"Unknown Logical Operation in class LogicalOperationNode \n";
					return false;
				}
		}
	}
	const LogicalOperation _op;
	shared_ptr<Node> _left;
	shared_ptr<Node> _right;

};
