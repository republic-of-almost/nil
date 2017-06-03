#include <nil/data/audio.hpp>
#include <nil/node.hpp>
#include <data/data.hpp>
#include <graph/graph_data.hpp>
#include <graph/graph.hpp>
#include <utilities/utilities.hpp>
#include "common.hpp"


namespace Nil {
namespace Data {


void
get(const Node &node, Audio &out)
{
  NIL_DATA_GETTER_SETTER_HAS_SETUP

  if(!getter_helper(
        node.get_id(),
        graph->component_data.audio_node_id,
        graph->component_data.audio_data,
        out))
  {
    NIL_DATA_GETTER_ERROR(Audio)
  }
}


void
set(Node &node, const Audio &in)
{
  NIL_DATA_GETTER_SETTER_HAS_SETUP

  if(!setter_helper(
    node,
    graph->component_data.audio_node_id,
    graph->component_data.audio_data,
    in,
    get_type_id(in)))
  {
    NIL_DATA_SETTER_ERROR(Audio)
  }
}


bool
has_audio(const Node &node)
{
  NIL_DATA_GETTER_SETTER_HAS_SETUP
  
  return has(node.get_id(), graph->component_data.audio_node_id);
}


uint64_t
get_type_id(const Audio &)
{
  NIL_DATA_TYPE_ID_REG
}


} // ns
} // ns
