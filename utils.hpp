#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <map>

struct Layer {
    std::string n_nodes;
    std::string nodelabel;
    std::string name;
    std::string connected_to_next_by;

};

Layer* copy_layer(Layer* src){

    Layer* dst = new Layer;
    dst->n_nodes = src->n_nodes;
    dst->nodelabel = src->nodelabel;
    dst->name = src->name;
    dst->connected_to_next_by = src->connected_to_next_by;
    return dst;
}

class Graph {

    public:
	std::map<std::string, std::string> connections;
	std::string graphtext;
	std::vector<Layer*> layer_list;
	Graph() {
	}

    void insert_text(std::string& to_insert){
	graphtext += to_insert;
    }

    std::string make_graph() {

	graphtext = "digraph G {\n\tfontname = \"Hilda 10\"\n\trankdir=LR\n\tsplines=line\n\tnodesep=0.8;\n\tranksep=5;\n\tedge [color=black, arrowsize=.2];\n\tnode [fixedsize=true,label=\"\",style=filled,color=none,fillcolor=gray,shape=circle]\n";

	int cluster_count = 0;
	std::vector<std::vector<std::string> > nodevec;
	for (int i=0; i<layer_list.size(); ++i) {
	    Layer* layer = layer_list[i];
	    int n_nodes = std::stoi(layer->n_nodes);
	    if (n_nodes < 1) exit(EXIT_FAILURE);
	    nodevec.push_back(subgraph_text(n_nodes, cluster_count, layer->name));
	    ++cluster_count;
	}

	for(unsigned int i=0; i<nodevec.size()-1; ++i){
	    std::vector<std::string> l1 = nodevec[i];
	    std::vector<std::string> l2 = nodevec[i+1];
	    for(unsigned int j=0; j<l1.size(); ++j){
		for(unsigned int k=0; k<l2.size(); ++k){
		    graphtext += "\n\t\t";
		    graphtext += l1[j] + " -> " + l2[k];
		}
	    }
	}

	graphtext += "\n}";
	std::ofstream file("graph.dot.out");
	file << graphtext;
	file.close();
	std::cout << "Wrote dot code to file (graph.dot.out)" << std::endl;
	std::cout << "Run dot -Tpdf graph.dot.out -o test.pdf to get dot output"<<std::endl;
	exit(EXIT_SUCCESS);
	return graphtext;
    }

    std::vector<std::string> subgraph_text(int n_nodes, int cluster_count,
	    std::string nodelabel) {

	auto format = "\t\t subgraph cluster_%d \{\n\t\t\tcolor=none\n\t\t\tnode [style=filled, color=white, penwidth=15, fillcolor=gray, shape=circle];\n\t\t\t %s;";

	std::string node_labels;
	std::vector<std::string> node_vector;
	for (int i=0; i<n_nodes; ++i){
	    std::string atomic = std::to_string(i) + 
		std::to_string(cluster_count);

	    node_labels = node_labels + " " + atomic;
	    node_vector.push_back(atomic);
	}
	auto size = std::snprintf(nullptr, 0, format, cluster_count, 
		node_labels.c_str());

	std::string output(size + 1, '\0');

	std::sprintf(&output[0], format, cluster_count, node_labels.c_str());
	graphtext += output;

	if (nodelabel.size()) {
	    graphtext +=  "\n\t\t\tlabel = "+ nodelabel + "\t\n}\n";
	}
	else {
	    graphtext +=  "\t\n}\n";
	}

	return node_vector;
    }

    void add_node(Layer* layer){
	layer_list.push_back(layer);
    }

};
