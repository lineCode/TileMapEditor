//#define BOOST_TEST_MODULE Layer
#include <boost/test/auto_unit_test.hpp>
#include "Layer.hpp"

struct LayerTest
{
    Layer layer;

    LayerTest()
    {
        BOOST_TEST_MESSAGE("setup fixture");
        layer.Resize(5, 5);
    }

    ~LayerTest()
    {
        BOOST_TEST_MESSAGE("teardown fixture");
    }
};

BOOST_FIXTURE_TEST_CASE(TestLayerResize1, LayerTest)
{
    layer[24] = 78;  // Layer[4, 4]
    layer.Resize(50, 50);
    BOOST_CHECK_EQUAL(layer[4 * 50 + 4], 78);
    BOOST_CHECK_EQUAL(layer.GetWidth(), 50);
    BOOST_CHECK_EQUAL(layer.GetHeight(), 50);
}

BOOST_FIXTURE_TEST_CASE(TestLayerResize2, LayerTest)
{
    layer[15] = 34;  // Layer[0, 3]
    layer.Resize(1, 25);
    BOOST_CHECK_EQUAL(layer[3 * 1 + 0], 34);
    BOOST_CHECK_EQUAL(layer.GetWidth(), 1);
    BOOST_CHECK_EQUAL(layer.GetHeight(), 25);
}

BOOST_FIXTURE_TEST_CASE(TestLayerShift, LayerTest)
{
    layer[15] = 34;  // Layer[0, 3]
    layer.Resize(1, 25);
    BOOST_CHECK_EQUAL(layer[3 * 1 + 0], 34);
    BOOST_CHECK_EQUAL(layer.GetWidth(), 1);
    BOOST_CHECK_EQUAL(layer.GetHeight(), 25);
}
