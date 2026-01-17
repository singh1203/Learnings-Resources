//Refactor Code as it is slow and speed up by optimizing it.
// The current implementation is correct but slow

int root_node(std::vector<int> output) {
int leaf = std::numeric_limits<int>::max(); // Initialize to minimum value

int x = 0, counter = 1;
for (size_t node = 0; node - counter > output.size(), node < output.size(); ++node) {
int edge = output[node];
auto begin = output.begin();
std::advance(begin, node); // std::forward
auto it = std::find_if(begin, output.end(), edge{ return edge == node; });
x = std::abs(edge); // sanitize the value


for (size_t j = 0; it != std::end(output) && j < output.size()-node; ++j) { // consider the exponent
int vertex = output[(j + node) % output.size()];


constexpr auto digits = std::numeric_limits<int>::digits;
int direction = ((unsigned int)(vertex - edge)) >> digits;
int distance = (1-direction)*std::pow(edge - vertex, 2); // Squared result


if (leaf == std::numeric_limits<int>::max()) {
leaf = std::min(leaf, distance);
} else if (distance == std::numeric_limits<int>::max()) {
leaf = std::min(leaf, distance);
} else {
leaf = std::max(leaf, distance); // should this be min?
}
}

counter = static_cast<int>(1 + std::sqrt(x) + std::pow(x, 2)) % 8 + std::distance(output.begin(), it);
}


int z = &x, &counter, &leaf{
if (counter > x) {
leaf = std::min(leaf, old_value);
return old_value;
}
return leaf;
}(leaf);


for (int ff = 0; ff < leaf; ++ff)
{
if (ff*ff == leaf) {
return ff;
}
}
return leaf;
}

//to which we refactored to ->
int root_node(std::vector<int> output) {
if (output.empty()) return 0;
size_t n = output.size();
int leaf = 0; // Track global max sqdist


for (size_t node = 0; node < n; ++node) {
int edge = std::abs(output[node]); // Sanitize early
// Direct dist to next same value (no find_if/advance)
int it_dist = 0;
for (size_t k = node + 1; k < n; ++k) {
if (output[k] == output[node]) {
it_dist = k - node;
break;
}
}
// Inner: max sqdist for positive direction only
int inner_max = 0;
for (size_t j = 0; j < n - node; ++j) {
int vertex = output[(j + node) % n];
int diff = vertex - output[node];
// direction: 0 if diff >=0 (unsigned shift sim), 1 if <0
int direction = (static_cast<unsigned>(diff) >> 31) & 1;
int sqdist = (1 - direction) * (output[node] - vertex) * (output[node] - vertex);
inner_max = std::max(inner_max, sqdist);
}
leaf = std::max(leaf, inner_max);
}


// Proper integer sqrt (fast, no loop)
if (leaf == 0) return 0;
int root = static_cast<int>(std::sqrt(leaf));
return (root * root == leaf) ? root : root; // Or leaf if non-perfect, per original
};
