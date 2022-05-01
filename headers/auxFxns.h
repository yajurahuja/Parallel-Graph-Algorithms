#ifndef AUX_FXNS_H
#define AUX_FXNS_H

#include<string>
#include<vector>


class AuxFxns
{
    public:
    static bool LoadGraphFromJason(long graphNumber, const std::string &filename, std::vector<int> &vertices, std::vector<std::pair<int, int> > &edges);
    static bool LoadGraphFromTxtFiles(long graphNumber, 
                                      const std::string &filename, 
                                      std::vector<long> &vertices, 
                                      std::vector<std::pair<long, long> > &edges,
                                      std::vector<double> &weights);
    static bool LoadUndirectedGraphFromTxtFiles(long graphNumber, 
                                const std::string &filename, 
                                std::vector<long> &vertices,
                                std::vector<std::pair<long , long> > &edges,
                                std::vector<double> &weights);

    static bool LoadUndirectedGraphFromTxtFiles(long graphNumber, 
                                    const std::string &filename, 
                                    std::vector<int> &vertices,
                                    std::vector<std::pair<int, int> > &edges,
                                    std::vector<double> &weights);

};

#endif