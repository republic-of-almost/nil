#ifndef NODE_INCLUDED_83839DB1_FCF2_4E9D_A4A5_D8491B0024C8
#define NODE_INCLUDED_83839DB1_FCF2_4E9D_A4A5_D8491B0024C8


#include <nil/fwd.hpp>
#include <stdint.h>
#include <stddef.h>


namespace Nil {


class Node final
{
public:

  explicit
  Node();
  
  Node(const decltype(nullptr));
  
  explicit
  Node(const uint32_t node_id, const bool is_owning = false);
    
  ~Node();
  
  
  // -------------------------------------------------------- [ Copy / Move ] --


  Node(const Node &other);
  Node& operator=(const Node &other);

  Node(Node &&other) noexcept;
  Node& operator=(Node &&other) noexcept;
  
  
  // ---------------------------------------------------------- [ Operators ] --
  
  
  bool
  operator==(const Node &other) const;
  
  
  bool
  operator!=(const Node &other) const;
  
  
  operator bool() const;
  

  // -------------------------------------------------------------- [ State ] --
  

  /*!
   *  Force destroy the node, all dependents will be destroyed as well.
   *  You can destroy nodes through references.
   */
  bool
  destroy();


  /*!
   *  Returns true if the this node is a reference or not. Owned top level
   *  nodes are never references.
   */
  bool
  is_ref() const;


  /*!
   *  Returns true if the node has no parent and is a top level node. All
   *  child nodes become references.
   */
  bool
  is_top_level() const;


  /*!
   *  Returns true if the node is valid, a node can be invalided by a ref
   *  forcing a delete.
   */
  bool
  is_valid() const;


  // ------------------------------------------------------ [ Relationships ] --


  /*!
   *  Set the parent of this node, making this node a child.
   *
   *  Returns false if it failed to add. This will occur if the node isn't
   *  a valid node.
   */
  bool
  set_parent(const Node &other);


  /*!
   * Returns the parent node. If no parent you will get an invalid entity.
   */
  Node
  get_parent() const;


  /*!
   *  Retuns the number of direct children, doesn't included other grand
   *  children etc.
   */
  size_t
  get_child_count() const;
  
  
  /*!
   *  Get the (n)th child.
   */
  Node
  get_child(const size_t i) const;


  /*!
   * Returns all the count of children and grandchildren etc.
   */
  size_t
  get_descendant_count() const;
  
  
  // --------------------------------------------------------------- [ Misc ] --
  
  
  const char*
  get_name() const;
  
  
  void
  set_name(const char *);
  
  
  /*!
   * Internal mechanism to get a the node ID.
   */
  uint32_t
  get_id() const;
  
  /*!
   *  Returns the last graph tick this node was edited.
   */
  uint64_t
  get_last_update() const;
  
  /*!
   *  Returns the type id of the node data.
   */
  uint64_t
  get_data_type_id() const;
  
  /*!
   * Set the data type id
   */
  void
  set_data_type_id(const uint64_t type_id);
  

private:

  mutable uint32_t        m_node_id;

}; 


} // ns


#endif // inc guard
