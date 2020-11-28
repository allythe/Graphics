#ifndef GRID_H
#define GRID_H
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "buttons.h"

using namespace Graph_lib;

struct My_window : Simple_window
{
    My_window(Point xy, int w, int h, const std::string &title)
        : Simple_window{xy, w, h, title},
          quit_button{Point{x_max() - 70, 20}, 70, 20, "Quit", cb_quit}
    {
        attach(quit_button);
    }

    Graph_lib::Button quit_button;

private:
    static void cb_quit(Address, Address addr) { Graph_lib::reference_to<My_window>(addr).quit(); }

    void quit() { hide(); }
};


class Grid : public My_window
{
public:
    Grid(Point p);

    static constexpr int N_h = 4;
    static constexpr int N_w = 6;

private:

    Graph_lib::Vector_ref<Buttons> my_btns;

    Graph_lib::Out_box anss;
    Graph_lib::Out_box qst;

    static constexpr int margin = 40;
    static constexpr int H_of_box = 40;
    static constexpr int W_of_box = N_w * Buttons::size_w + 2 * margin + 70;
    static constexpr int width = N_w * Buttons::size_w + 2 * margin + 70;
    static constexpr int height = N_h * Buttons::size_h + 2 * margin + H_of_box * 2;

    std::string expression;

    void make_btn(int i, int j, Callback cb, const std::string& name);

    Buttons &at(Point p);

    static void cb_expr(Address widget, Address win)
    {
        Graph_lib::reference_to<Grid>(win).expr(widget);
    }

    static void cb_result(Address widget, Address win)
    {
        Graph_lib::reference_to<Grid>(win).result(widget);
    }

    static void cb_help(Address widget, Address win)
    {
        Graph_lib::reference_to<Grid>(win).help(widget);
    }

    void expr(Address widget);
    void result(Address widget);
    void help(Address widget);
};



#endif // GRID_H
