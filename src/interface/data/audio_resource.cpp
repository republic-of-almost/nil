#include <nil/data/audio_resource.hpp>
#include <nil/node.hpp>
#include <data/data.hpp>
#include <graph/graph_data.hpp>
#include <graph/graph.hpp>
#include <utilities/utilities.hpp>
#include "common.hpp"


namespace Nil {
namespace Data {


void
get(const Node &node, Audio_resource &out)
{
  NIL_DATA_GETTER_SETTER_HAS_SETUP

  if(!getter_helper(
        node.get_id(),
        graph->component_data.audio_resource_node_id,
        graph->component_data.audio_resource_data,
        out))
  {
    NIL_DATA_GETTER_ERROR(Audio_resource)
  }
}


void
set(Node &node, const Audio_resource &in)
{
  NIL_DATA_GETTER_SETTER_HAS_SETUP

  if(!setter_helper(
    node,
    graph->component_data.audio_resource_node_id,
    graph->component_data.audio_resource_data,
    in,
    get_type_id(in)))
  {
    NIL_DATA_SETTER_ERROR(Audio_resource)
  }
}


bool
has_audio_resource(const Node &node)
{
  NIL_DATA_GETTER_SETTER_HAS_SETUP
  
  return has(node.get_id(), graph->component_data.audio_resource_node_id);
}


uint64_t
get_type_id(const Audio_resource &)
{
  NIL_DATA_TYPE_ID_REG
}


} // ns
} // ns