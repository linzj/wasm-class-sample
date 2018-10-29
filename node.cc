#include "node.h"
#include <sstream>
#include "emscripten/bind.h"
using namespace emscripten;

Node::Node(std::string n)
    : parent_(nullptr),
      sibling_(nullptr),
      first_child_(nullptr),
      name_(std::move(n)),
      width_(0),
      height_(0) {}

void Node::SetWidth(int width) {
  width_ = width;
}

void Node::SetHeight(int height) {
  height_ = height;
}

int Node::GetWidth() const {
  return width_;
}

int Node::GetHeight() const {
  return height_;
}

void Node::AppendChild(Node* node) {
  node->parent_ = this;
  if (!first_child_)
    first_child_ = node;
  else {
    Node* last;
    Node* now = first_child_;
    while (now) {
      last = now;
      now = now->sibling_;
    }
    last->sibling_ = node;
    node->sibling_ = nullptr;
  }
}

Node* Node::GetParent() {
  return parent_;
}

std::string Node::GetStyle() const {
  return style_;
}

std::string Node::GetName() const {
  return name_;
}

void Node::SetStyle(const std::string& style) {
  style_ = style;
}

void Node::SetName(const std::string& name) {
  name_ = name;
}

void Node::DoBuildHTML(std::ostream& os) {
  std::ostringstream size_style;
  size_style << "width:" << width_ << "px"
             << ";height:" << height_ << "px;";
  std::ostringstream style;
  os << "<div style=\"" << size_style.str() << style_ << "\">" << name_;
  if (first_child_)
    first_child_->DoBuildHTML(os);
  if (sibling_)
    sibling_->DoBuildHTML(os);
  os << "</div>";
}

std::string Node::BuildHTML() {
  std::ostringstream output;
  DoBuildHTML(output);
  return output.str();
}

EMSCRIPTEN_BINDINGS(Node) {
  class_<Node>("Node")
      .constructor<std::string>()
      .property("width", &Node::GetWidth, &Node::SetWidth)
      .property("height", &Node::GetHeight, &Node::SetHeight)
      .property("style", &Node::GetStyle, &Node::SetStyle)
      .function("appendChild", &Node::AppendChild, allow_raw_pointers())
      .function("getParent", &Node::GetParent, allow_raw_pointers())
      .function("buildHTML", &Node::BuildHTML);
}
