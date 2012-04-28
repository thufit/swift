#ifndef CELL_H_
#define CELL_H_

class Cell
{
public:
	Cell() : _src(-1), _dest(-1), _size(-1), _birth(-1), _death(-1), _empty(true) {}
	
	bool empty() const { return _empty; }

	void setSrc(int x) { setEmpty(); _src = x; }
	void setDest(int x ) { setEmpty(); _dest = x; }
	void setSize(int x) { setEmpty(); _size = x; }
	void setBirth(int x) { setEmpty(); _birth = x; }
	void setDeath(int x) {  setEmpty(); _death = x; }

	int getSrc() const { return _src; }
	int getDest() const { return _dest; }
	int getSize() const{ return _size; }
	int getBirth() const { return _birth; }
	int getDeath() const { return _death; }
private:
	void setEmpty() { _empty = true; }
private:
	int _src;
	int _dest;
	int _size;
	int _birth;
	int _death;
	bool _empty;

};

#endif
