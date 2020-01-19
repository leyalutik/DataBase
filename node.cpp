
#include "node.h"
using namespace std;





	EmptyNode::EmptyNode(){}



DateComparisonNode::DateComparisonNode(const Comparison cmp,const Date& bound):
		_cmp(cmp),_bound(bound.date){}




EventComparisonNode::EventComparisonNode( const Comparison cmp,const string& bound):
		_cmp(cmp),_bound(bound){}


LogicalOperationNode::LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left,
		shared_ptr<Node> right):_op(op),_left(left),_right(right){}
	void LogicalOperationNode::Set_Left(shared_ptr<Node> left){
		LogicalOperationNode::_left = left;
	}
	void LogicalOperationNode::Set_Right(shared_ptr<Node> right){
		_right = right;
	}

