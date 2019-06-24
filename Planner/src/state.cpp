#include "state.h"
#include <iostream>
#include <algorithm>

State::State() {
    father_ = nullptr;
}

State::~State() {
    if (father_ != nullptr)
        father_->RemoveChild(this);
}

int State::GetDepth() {
    return depth_;
}

void State::SetDepth(int d) {
    depth_ = d;
}

void State::SetFather(State *father) {
    this->father_ = father;
}

void State::SetHvalue(double h) {
    hvalue_ = h;
}

double State::GetHvalue() {
    return hvalue_;
}

State *State::GetFather() {
    return father_;
}

void State::RemoveChild(State *child) {
    children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
}
