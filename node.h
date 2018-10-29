#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
class Node {
 public:
  Node(std::string);
  ~Node();
  int GetWidth() const;
  int GetHeight() const;
  void SetWidth(int);
  void SetHeight(int);
  void AppendChild(Node*);
  Node* GetParent();
  std::string GetStyle() const;
  std::string GetName() const;
  void SetStyle(const std::string&);
  void SetName(const std::string&);
  std::string BuildHTML();

 private:
  void DoBuildHTML(std::ostream& os);
  Node* parent_;
  Node* sibling_;
  Node* first_child_;
  std::string name_;
  std::string style_;
  int width_, height_;
};
#endif  // NODE_H
