#pragma once
class TreeNode
{
public:
	TreeNode();
	~TreeNode();

	char RGB_T[4];
	unsigned int this_w;
	unsigned int this_h;

	unsigned int child_count;

	TreeNode * left;
	TreeNode * middle_left;
	TreeNode * middle_right;
	TreeNode * right;

	void add_colours(char r, char g, char b);
	void setDims(unsigned int w, unsigned int h);
	void give_birth();
};

