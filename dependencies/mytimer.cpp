#ifndef MYTIMER_H
#define MYTIMER_H
    #include<iostream>
    #include<chrono>
    class Timer {
        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> startpoint;
            std::chrono::time_point<std::chrono::high_resolution_clock> endpoint;
        public:
            Timer(){
                startpoint = std::chrono::high_resolution_clock::now();
            }
            ~Timer(){
                Stop();
            }

            void Stop(){
                endpoint = std::chrono::high_resolution_clock::now();
                auto start  = std::chrono::time_point_cast<std::chrono::microseconds>(startpoint).time_since_epoch().count();
                auto end    = std::chrono::time_point_cast<std::chrono::microseconds>(endpoint).time_since_epoch().count();
                auto duration = end - start;
                std::cerr<<"Time Duration: "<<duration*0.001<<"ms or "<<duration*0.000001<<"s"<<std::endl;
            }
    };
#endif