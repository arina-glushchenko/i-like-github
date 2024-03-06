<<<<<<< HEAD
#include "circular_buffer.h"
=======
#include "../include/circular_buffer.h"
>>>>>>> 066a262c681c591eccc5c90d5aca1eea92cc1481
#include <stdexcept>
#include <string_view>
#include <iostream>
//#define __PRETTY_FUNCTION__ __FUNCSIG__

typedef char value_type;

CircularBuffer::CircularBuffer() { //1
	buffer = nullptr;
	start = 0;
	end = 0;
	bufferSize = 0;
	bufferCapacity = 0;
}

CircularBuffer::~CircularBuffer() {
	delete[] buffer;
}
CircularBuffer::CircularBuffer(const CircularBuffer& cb) { //2
	bufferSize = cb.bufferSize;
	bufferCapacity = cb.bufferCapacity;
	buffer = new value_type[bufferCapacity];
	for (int i = 0; i < bufferSize; i++) {
		buffer[i] = cb.buffer[i];
	}
	start = cb.start;
	end = cb.end;
}

//Êîíñòðóèðóåò áóôåð çàäàííîé ¸ìêîñòè.
CircularBuffer::CircularBuffer(int capacity) { //3
	start = bufferSize = 0;
	buffer = new value_type[capacity];
	bufferCapacity = capacity;
	end = bufferSize - 1;
}


//Êîíñòðóèðóåò áóôåð çàäàííîé ¸ìêîñòè, öåëèêîì çàïîëíÿåò åãî ýëåìåíòîì elem.
CircularBuffer::CircularBuffer(int capacity, const value_type& elem) {
	start = 0;
	bufferSize = capacity;
	bufferCapacity = capacity;
	buffer = new value_type[capacity];
	for (int i = 0; i < bufferSize; i++)
	{
		buffer[i] = elem;
	}
	end = capacity - 1;
}

//Äîñòóï ïî èíäåêñó. Íå ïðîâåðÿþò ïðàâèëüíîñòü èíäåêñà.
value_type& CircularBuffer::operator[](int i) { //4
	return buffer[(start + i) % bufferCapacity];
}
const value_type& CircularBuffer::operator[](int i) const {
	return buffer[(start + i) % bufferCapacity];
}

//Äîñòóï ïî èíäåêñó. Ìåòîäû áðîñàþò èñêëþ÷åíèå â ñëó÷àå íåâåðíîãî èíäåêñà.
value_type& CircularBuffer::at(int i) { //5
	if (i < 0 || i >= bufferSize) {
		throw std::out_of_range("Invalid index");
	}
	else {
		return buffer[(start + i) % bufferCapacity];
	}
}
const value_type& CircularBuffer::at(int i) const {
	if (i < 0 || i > bufferSize) {
		throw std::out_of_range("Invalid index");
	}
	else {
		return buffer[(start + i) % bufferCapacity];
	}
}

//Ññûëêà íà ïåðâûé ýëåìåíò.
value_type& CircularBuffer::front() { //6
	return buffer[start];
}

//Ññûëêà íà ïîñëåäíèé ýëåìåíò.
value_type& CircularBuffer::back() { //7
	return buffer[end];
}
const value_type& CircularBuffer::front() const {
	return buffer[start];
}

const value_type& CircularBuffer::back() const {
	return buffer[end];
}

//Ëèíåàðèçàöèÿ - ñäâèíóòü êîëüöåâîé áóôåð òàê, ÷òî åãî ïåðâûé ýëåìåíò
//ïåðåìåñòèòñÿ â íà÷àëî àëëîöèðîâàííîé ïàìÿòè. Âîçâðàùàåò óêàçàòåëü 
//íà ïåðâûé ýëåìåíò.

value_type* CircularBuffer::linearize() { //8
	value_type* newBuffer = new value_type[bufferSize];
	for (int i = 0; i < bufferSize; i++) {
		newBuffer[i] = buffer[(start + i) % bufferCapacity];
	}
	buffer = newBuffer;
	start = 0;
	end = bufferSize - 1;
	return buffer;
}

//Ïðîâåðÿåò, ÿâëÿåòñÿ ëè áóôåð ëèíåàðèçîâàííûì.
bool CircularBuffer::is_linearized() const { //9
	return start == 0 && end == bufferSize - 1;
}
//Ñäâèãàåò áóôåð òàê, ÷òî ïî íóëåâîìó èíäåêñó îêàæåòñÿ ýëåìåíò 
//ñ èíäåêñîì new_begin.
void CircularBuffer::rotate(int new_begin) { //10
	if (new_begin < 0 || new_begin >= bufferSize) {
		throw std::out_of_range("Invalid new_begin");
	}
	int shift = (new_begin - start + bufferSize) % bufferSize;
	start = (start + shift) % bufferCapacity;
	end = (end + shift) % bufferCapacity;
}

//Êîëè÷åñòâî ýëåìåíòîâ, õðàíÿùèõñÿ â áóôåðå.
int CircularBuffer::size() const { //11
	return bufferSize;
}
bool CircularBuffer::empty() const { //12
	return bufferSize == 0;
}
//true, åñëè size() == capacity().
bool CircularBuffer::full() const { //13
	if (bufferSize == 0 && bufferCapacity == 0) {
		return false;
	}
	else {
		return bufferSize == bufferCapacity;
	}
}
//Êîëè÷åñòâî ñâîáîäíûõ ÿ÷ååê â áóôåðå.
int CircularBuffer::reserve() const { //14
	return bufferCapacity - bufferSize;
}
//¸ìêîñòü áóôåðà
int CircularBuffer::capacity() const { //15
	return bufferCapacity;
}

void CircularBuffer::set_capacity(int new_capacity) { //16
	if (new_capacity < bufferSize) {
		throw std::length_error("New capacity is smaller than buffer size");
	}
	value_type* newBuffer = new value_type[new_capacity];
	for (int i = 0; i < bufferCapacity; i++) {
		newBuffer[i] = buffer[(start + i) % bufferCapacity];
	}
	buffer = newBuffer;
	bufferCapacity = new_capacity;
}
//Èçìåíÿåò ðàçìåð áóôåðà.
//Â ñëó÷àå ðàñøèðåíèÿ, íîâûå ýëåìåíòû çàïîëíÿþòñÿ ýëåìåíòîì item.
void CircularBuffer::resize(int new_size, const value_type& item) { //17
	if (new_size < 0) {
		throw std::invalid_argument("Invalid new_size");
	}
	if (new_size == bufferSize) {
		return;
	}

	if (new_size < bufferSize) {
		bufferSize = new_size;
		end = (start + bufferSize - 1) % bufferCapacity;
	}
	else {
		value_type* newBuffer = new value_type[new_size];
		for (int i = 0; i < bufferSize; i++) {
			newBuffer[i] = buffer[(start + i) % bufferCapacity];
		}
		for (int i = bufferSize; i < new_size; i++) {
			newBuffer[i] = item;
		}
		delete[] buffer;
		buffer = newBuffer;
		bufferSize = new_size;
		bufferCapacity = new_size;
		start = 0;
		end = new_size - 1;
	}
}
//Îïåðàòîð ïðèñâàèâàíèÿ.
CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb) { //18
	delete[] buffer;
	bufferSize = cb.bufferSize;
	bufferCapacity = cb.bufferCapacity;
	buffer = new value_type[bufferCapacity];
	for (int i = 0; i < bufferSize; i++) {
		buffer[i] = cb.buffer[i];
	}
	start = cb.start;
	end = cb.end;
	return *this;
}
//Îáìåíèâàåò ñîäåðæèìîå áóôåðà ñ áóôåðîì cb.
void CircularBuffer::swap(CircularBuffer& cb) { //19
	if (bufferCapacity != cb.bufferCapacity) {
		throw std::length_error("Buffers have different capacities");
	}
	value_type* tempBuffer = buffer;
	buffer = cb.buffer;
	cb.buffer = tempBuffer;
	int tempStart = start;
	start = cb.start;
	cb.start = tempStart;
	int tempEnd = end;
	end = cb.end;
	cb.end = tempEnd;
	int tempBufferSize = bufferSize;
	bufferSize = cb.bufferSize;
	cb.bufferSize = tempBufferSize;
}

//Äîáàâëÿåò ýëåìåíò â êîíåö áóôåðà. 
//Åñëè òåêóùèé ðàçìåð áóôåðà ðàâåí åãî ¸ìêîñòè, òî ïåðåïèñûâàåòñÿ
//ïåðâûé ýëåìåíò áóôåðà (ò.å., áóôåð çàêîëüöîâàí). 
void CircularBuffer::push_back(const value_type& item) { //20
	if (full()) {
		start = (start + 1) % bufferCapacity; 
	}
	else if (empty()) {
		start = 0;
	}
	end = (end + 1) % bufferCapacity;
	buffer[end] = item; 
	bufferSize++;
}

//Äîáàâëÿåò íîâûé ýëåìåíò ïåðåä ïåðâûì ýëåìåíòîì áóôåðà. 
//Àíàëîãè÷íî push_back, ìîæåò ïåðåïèñàòü ïîñëåäíèé ýëåìåíò áóôåðà.
void CircularBuffer::push_front(const value_type& item) { //21
	if (full()) {
		end = (end - 1 + bufferCapacity) % bufferCapacity; 
	}
	else if (empty()) {
		end = bufferSize; 
	}
	start = (start - 1 + bufferCapacity) % bufferCapacity; 
	buffer[start] = item; 
	bufferSize++; 
}

//óäàëÿåò ïîñëåäíèé ýëåìåíò áóôåðà.
void CircularBuffer::pop_back() { //22
	if (empty()) {
		throw std::out_of_range("Buffer is empty, cannot pop_back");
	}
	if (start == end) {
		start = 0;
		end = 0;
	}
	else {
		end = (end - 1 + bufferCapacity) % bufferCapacity;
	}
	bufferSize--;
}

//óäàëÿåò ïåðâûé ýëåìåíò áóôåðà.
void CircularBuffer::pop_front() { //23
	if (empty()) {
		throw std::out_of_range("Buffer is empty, cannot pop_front");
	}
	if (start == end) {
		start = 0;
		end = 0;
	}
	else {
		start = (start + 1) % bufferCapacity; 
	}
	bufferSize--;
}

//Âñòàâëÿåò ýëåìåíò item ïî èíäåêñó pos. ¨ìêîñòü áóôåðà îñòàåòñÿ íåèçìåííîé.
void CircularBuffer::insert(int pos, const value_type& item) { //24
	if (pos < 0 || pos > bufferSize) {
		throw std::out_of_range("Invalid index");
	}
	if (full()) {
		throw std::length_error("Buffer is full, cannot insert");
	}

	for (int i = end; i >= start; i--) {
		buffer[(i + 1) % bufferCapacity] = buffer[i % bufferCapacity];
		if (i == pos) {
			buffer[i % bufferCapacity] = item;
			break;
		}
	}

	end = (end + 1) % bufferCapacity;
	bufferSize++; 
}

//Óäàëÿåò ýëåìåíòû èç áóôåðà â èíòåðâàëå [first, last).
void CircularBuffer::erase(int first, int last) { //25
	if (first < 0 || first >= last || last > bufferSize) {
		throw std::out_of_range("Invalid range");
	}

	int eraseCount = last - first +1;
	int shiftCount = bufferSize - last;
	int srcIndex = (start + last) % bufferCapacity;
	int destIndex = (start + first) % bufferCapacity;

	for (int i = 0; i < shiftCount; i++) {
		buffer[destIndex] = buffer[srcIndex];
		destIndex = (destIndex + 1) % bufferCapacity;
		srcIndex = (srcIndex + 1) % bufferCapacity;
	}

	end = (end - eraseCount + bufferCapacity) % bufferCapacity;
	bufferSize -= eraseCount;
}

//Î÷èùàåò áóôåð.
void CircularBuffer::clear() { //26
	start = 0;
	end = 0;
	bufferSize = 0;
}

//CircularBuffer::CircularBuffer(CircularBuffer&& other) {
//	this->buffer = other.buffer;
//	other.buffer = nullptr;
//	std::cout << __PRETTY_FUNCTION__ << " // steal 1G" << std::endl;
//}


//CircularBuffer& CircularBuffer:: operator=(CircularBuffer&& other) {
//	std::cout << __PRETTY_FUNCTION__ << " // steal 1G" << std::endl;
//	std::swap(buffer, other.buffer);
//	return *this;
//}


bool operator==(const CircularBuffer& a, const CircularBuffer& b) { //27
	if (a.size() != b.size()) {
		return false; 
	}
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) {
			return false; 
		}
	}
	return true; 
}


// Îïåðàòîð ñðàâíåíèÿ !=
bool operator!=(const CircularBuffer& a, const CircularBuffer& b) { //28
	return !(a == b); 
}




