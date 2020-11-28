#include "grid.h"
#include "buttons.h"

#include <fstream>
#include"logic.h"


char sign[]{'1', '2', '3', '+', '=', ',', '4', '5', '6', '-', 'p', '.',
            '7', '8', '9', '*', '_', ')', 'h', '0', 'q', '/', '!', '('};

void Grid::make_btn(int i, int j, Callback cb, const std::string& name){
     std::cout<<"erotica"<<std::endl;
    my_btns.push_back(

        new Buttons{Point{margin + j * Buttons::size_w,
                          height - H_of_box - (2 * margin + (N_h - 1 - i) * Buttons::size_h)},
                    cb,
                    name });

    attach(my_btns[my_btns.size() - 1]);
}

Grid::Grid(Point xy)
    : My_window{xy, width, height, "Grid"}
     , anss{Point{x_max() - 410, 10}, 200, 40, "ANSWER"}
      , qst{Point{x_max() - 590, 60}, 480, 40, ""}
{
    attach(anss);
    attach(qst);
    size_range(width, height, width, height); //fixed window size

    make_btn(0,0, cb_expr, "1");
    make_btn(0,1, cb_expr, "2");
    make_btn(0,2, cb_expr, "3");
//    make_btn(1,0, cb_expr, "4");
//    make_btn(2,1, cb_expr, "5");
//    make_btn(2,2, cb_expr, "6");
//    make_btn(3,0, cb_expr, "7");
//    make_btn(3,1, cb_expr, "8");
//    make_btn(3,2, cb_expr, "9");

  //...
    make_btn(3,0, cb_result, "=");
    make_btn(3,1, cb_help, "help");


    for (int i = 0; i < my_btns.size(); ++i)
    {
        my_btns[i].label.push_back(sign[i]);
    }
}

void Grid::expr(Address widget)
{
    Fl_Widget &w = reference_to<Fl_Widget>(widget);
    Buttons& btn = at(Point{w.x(), w.y()});

    expression += btn.value();

    qst.put(expression);
}

void write_expr(const std::string& path, const std::string& expr){

    std::ofstream foutt{path}; // поток для записи

    if (foutt)
    {
        foutt << expr << std::endl;
    }
}

std::string read_answer(const std::string& path){

    std::ifstream ifs{path}; // поток для записи
    std::string line;

    if (ifs)
    {
       std::getline(ifs,line);
    }

    return line;
}

void Grid::result(Address)
{
    write_expr("expression.txt", expression);
    calculate();

    std::string ans = read_answer("ans.txt");

    anss.put(ans);

    Fl::redraw();
}

void Grid::help(Address widget){
    //...
}


Buttons & Grid::at(Point p)
{
    int i = (height - H_of_box - p.y - margin) / Buttons::size_h;
    int j = (p.x - margin) / Buttons::size_w;
    std::cout << i <<" "<< j<< std::endl;
    return my_btns[i * N_w + j];
}



