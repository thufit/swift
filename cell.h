#ifndef CELL_H_
#define CELL_H_

class Cell
{
public:
	Cell() : src_(-1), dest_(-1), size_(-1), birth_(-1), death_(-1), empty_(true) {}
	bool Empty() const { return empty_; }
	
	void set_empty(bool b = true) { empty_ = b; }
	void set_src(int x) { set_empty(false); src_ = x; }
	void set_dest(int x ) { set_empty(false); dest_ = x; }
	void set_size(int x) { set_empty(false); size_ = x; }
	void set_birth(int x) { set_empty(false); birth_ = x; }
	void set_death(int x) {  set_empty(false); death_ = x; }
	int get_src() const { return src_; }
	int get_dest() const { return dest_; }
	int get_size() const{ return size_; }
	int get_birth() const { return birth_; }
	int get_death() const { return death_; }

private:
	int src_;
	int dest_;
	int size_;
	int birth_;
	int death_;
	bool empty_;

};

#endif
