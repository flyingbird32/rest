#pragma once
#include "../rest.h"

class BaseController 
{
public:
    struct EndpointData 
    {
        std::string path;
        HTTP_METHOD method;
        Endpoint(*handler)(Request&);
    };

    virtual ~BaseController() = default;

    const std::vector<EndpointData>& getEndpoints() const 
    {
        return endpoints;
    }

protected:
    void registerEndpoint(const std::string& path, HTTP_METHOD method, Endpoint(*handler)(Request&)) 
    {
        endpoints.push_back({ path, method, handler });
    }

private:
    std::vector<EndpointData> endpoints;
};