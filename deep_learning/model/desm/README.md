### 简介

The Dual Embedding Space Model (DESM) is an information retrieval model that uses two word embeddings, one for query words and one for document words. It takes into account the vector similarity between each query word vector and all document word vectors.

A key challenge for information retrieval is to model document aboutness. The traditional approach uses term frequency, with more occurrences of a query word indicating that the document is more likely to be about that word. DESM uses multiple document words as aboutness evidence for each query term. For example, for the query term “Albuquerque” the two passages of text below are indistinguishable according to term frequency, each having one occurrence. Our approach considers the presence of related terms such as “population” and “metropolitan”, which is evidence that passage (a) is about Albuquerque while passage (b) merely mentions Albuquerque.

desm_aboutness

Here we generate our dual embeddings using the well-known tool word2vec. In most word2vec studies, word embeddings are taken from the model’s input matrix only (IN). In this paper we also use the output matrix (OUT) embeddings. In the table below, the IN vector for “Yale” is close to the IN vector for “Harvard” (IN-IN), but its nearest neighbour in OUT space is “Faculty” (IN-OUT). The single embedding approaches (IN-IN and OUT-OUT) tend to group words of the same type (typical), whereas the dual embedding approach (IN-OUT) groups words that occur together in the training data (topical).

desm-nearestneighbours

The DESM approach of performing all-pairs comparison with dual embeddings yields positive results on information retrieval testbeds. More details can be found in the publications listed below.


#### 应用场景

计算query与title的相似度, 可以认为是一种排序模型.


### 参考资料
- https://www.microsoft.com/en-us/research/project/dual-embedding-space-model-desm/
