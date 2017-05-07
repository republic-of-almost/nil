#include <nil/data/graphics.hpp>
#include <nil/node.hpp>
#include <data/data.hpp>
#include <graph/graph_data.hpp>
#include <graph/graph.hpp>
#include <utilities/utilities.hpp>
#include "common.hpp"


namespace Nil {
namespace Data {


void
get(const Node &node, Graphics &out)
{
  NIL_DATA_GETTER_SETTER_HAS_SETUP

  if(!getter_helper(
        node.get_id(),
        graph->component_data.graphics_node_id,
        graph->component_data.graphics_data,
        out))
  {
    NIL_DATA_GETTER_ERROR(Graphics)
  }
}


void
set(Node &node, const Graphics &in)
{
  NIL_DATA_GETTER_SETTER_HAS_SETUP

  if(!setter_helper(
    node,
    graph->component_data.graphics_node_id,
    graph->component_data.graphics_data,
    in,
    get_type_id(in)))
  {
    NIL_DATA_SETTER_ERROR(Graphics)
  }
}


bool
has_graphics(const Node &node)
{
  NIL_DATA_GETTER_SETTER_HAS_SETUP
  
  return has(node.get_id(), graph->component_data.graphics_node_id);
}


uint64_t
get_type_id(const Graphics &)
{
  NIL_DATA_TYPE_ID_REG
}


} // ns
} // ns
