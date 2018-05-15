#include "TreeNode.h"



TreeNode::TreeNode()
{
	this->child_count = 0;

}


TreeNode::~TreeNode()
{
}

void TreeNode::add_colours(char r, char g, char b) {
	RGB_T[0] = r;
	RGB_T[1] = g;
	RGB_T[2] = b;
	RGB_T[3] = 0xff;
}

void TreeNode::setDims(unsigned int w, unsigned int h) {
	this_w = w;
	this_h = h;
}

void TreeNode::give_birth() {

	left = new TreeNode();
	middle_left = new TreeNode();
	middle_right = new TreeNode();
	right = new TreeNode();
	this->child_count = 4;
}

