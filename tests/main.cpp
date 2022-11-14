#include <otx/otx.h>
#include <iostream>

int main(int argc, char *argv[]) {
    {
        otx::OptParse(argc, argv, std::cout);
    }

    {
        const char *args[] = {"", "test", "3foo"};
        otx::OptParse(3, args, std::cout);
    }

    {
        const char *args[] = {"", "test", "3foo"};
        auto val = otx::OptParse(3, args)["test"].to<std::string>();
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "3"};
        auto val = otx::OptParse(3, args)["test"].to<int>();
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "7.15"};
        auto val = otx::OptParse(3, args)["test"].to<float>();
        std::cout << val << std::endl;
    }

    std::cout << std::endl;

    {
        const char *args[] = {"", "test", "3foo"};
        auto val = otx::OptParse(3, args)["test"].to<std::string>("def");
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "3"};
        auto val = otx::OptParse(3, args)["test"].to<int16_t>(-1);
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "7.15"};
        auto val = otx::OptParse(3, args)["test"].to<float>(3.14);
        std::cout << val << std::endl;
    }

    std::cout << std::endl;

    {
        const char *args[] = {"", "test", "3foo"};
        auto val = otx::OptParse(3, args)["testx"].to<std::string>("def");
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "3"};
        auto val = otx::OptParse(3, args)["testx"].to<int16_t>(-1);
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "7.15"};
        auto val = otx::OptParse(3, args)["testx"].to<float>(3.14);
        std::cout << val << std::endl;
    }

    std::cout << std::endl;

    {
        const char *args[] = {"", "test", "3foo"};
        auto val = otx::OptParse(3, args)["testx"].to<std::string>("def");
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "3"};
        auto val = otx::OptParse(3, args)["testx"].to<int16_t>(-1);
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "7.15"};
        auto val = otx::OptParse(3, args)["testx"].to<float>(3.14);
        std::cout << val << std::endl;
    }

    std::cout << std::endl;

    {
        const char *args[] = {"", "test", "7.15"};
        auto val = otx::OptParse(3, args)[{"test"}].to<float>(3.14);
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "7.15"};
        auto val = otx::OptParse(3, args)[{"testx"}].to<float>(3.14);
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "7.15"};
        auto val = otx::OptParse(3, args)["testx", "test"].to<float>(3.14);
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "7.15"};
        auto val = otx::OptParse(3, args)["test", "testx"].to<float>(3.14);
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "3foo"};
        auto val = otx::OptParse(3, args)["test", "testx"].to<std::string>();
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "3"};
        auto val = otx::OptParse(3, args)["test", "testx"].to<int16_t>();
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "7.15"};
        auto val = otx::OptParse(3, args)["test", "testx"].to<float>();
        std::cout << val << std::endl;
    }

    {
        const char *args[] = {"", "test", "7.15,8.1452,15"};
        auto val = otx::OptParse(3, args)["test", "testx"].to<float[]>();
        for (auto v: val) { std::cout << v << " | "; }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    {
        try {
            const char *args[] = {"", "test", "3x"};
            auto val = otx::OptParse(3, args)["test", "testx"].to<int16_t>();
            std::cout << val << std::endl;
        } catch (const otx::IncorrectFormat &e) {
            std::cout << "IncorrectFormat" << std::endl;
            std::cout << e.what() << std::endl;

        }

    }

    {
        try {
            const char *args[] = {"", "test", "x3"};
            auto val = otx::OptParse(3, args)["test", "testx"].to<int16_t>();
            std::cout << val << std::endl;
        } catch (const otx::IncorrectFormat &e) {
            std::cout << "IncorrectFormat" << std::endl;
            std::cout << e.what() << std::endl;
        }
    }


    try {
        const char *args[] = {"", "test", "7.15"};
        auto val = otx::OptParse(3, args)["testx", "testz"].to<float>();
        std::cout << val << std::endl;
    } catch (const otx::NotFound &e) {
        std::cout << "NotFound" << std::endl;
        std::cout << e.what() << std::endl;
    }
}