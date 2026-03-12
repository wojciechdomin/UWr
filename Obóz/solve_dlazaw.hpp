#include <bits/stdc++.h>
#include <unistd.h>
#include <ext/stdio_filebuf.h>
#include <sys/wait.h>
#include <fcntl.h>

namespace Solve {

class Interactor {
public:
    static Interactor& create(int argc, char** argv) {
        instance().initialize(argc, argv);
        return instance();
    }
    static Interactor& instance() {
        static Interactor ret;
        return ret;
    }

    Interactor(Interactor const&) = delete;
    void operator=(Interactor const&) = delete;

    class InStream : public std::istream {
    public:
        explicit InStream(int fd)
            : std::istream(nullptr), buf(fd, std::ios::in) {
            rdbuf(&buf);
        }
    private:
        __gnu_cxx::stdio_filebuf<char> buf;
    };

    class OutStream : public std::ostream {
    public:
        explicit OutStream(int fd)
            : std::ostream(nullptr), buf(fd, std::ios::out) {
            rdbuf(&buf);
        }
    private:
        __gnu_cxx::stdio_filebuf<char> buf;
    };

    void end(int score, const std::string& msg) {
        assert_initialized();
        if (score < 0 || score > 100) {
            throw std::runtime_error("Score must be in range [0, 100]");
        }
        std::cout << score << "\n" << msg << std::endl;
        std::exit(0);
    }

    void fail(const std::string& msg) {
        end(0, msg);
    }

    void accept(const std::string& msg = "OK") {
        end(100, msg);
    }

    std::ifstream& test_reader() {
        return test_input;
    }

    std::pair<InStream&, OutStream&> reader_writer() {
        return { *reader_ptr, *writer_ptr };
    }

    InStream& reader(size_t _ignored) { return *reader_ptr; }
    OutStream& writer(size_t _ignored) { return *writer_ptr; }

private:
    Interactor() : initialized(false) {}

    bool initialized;

    std::ifstream test_input;

    std::unique_ptr<InStream> reader_ptr;
    std::unique_ptr<OutStream> writer_ptr;

    void assert_initialized() {
        if (!initialized) {
            throw std::runtime_error("Not initialized");
        }
    }

    void initialize(int argc, char** argv) {
        if (argc != 3) {
            std::cerr << "Usage: ./grader <testfile> <solution-exe>\n";
            std::exit(1);
        }
        if (initialized) {
            throw std::runtime_error("Cannot initialize interactor multiple times");
        }
        initialized = true;

        test_input = std::ifstream(argv[1]);
        std::string exe = argv[2];

        int to_child[2];
        int from_child[2];

        if (pipe(to_child) || pipe(from_child)) {
            perror("pipe");
            std::exit(1);
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            std::exit(1);
        }

        if (pid == 0) {
            // --- Child ---
            dup2(to_child[0], STDIN_FILENO);
            dup2(from_child[1], STDOUT_FILENO);

            close(to_child[1]);
            close(from_child[0]);

            execl(exe.c_str(), exe.c_str(), (char*)nullptr);
            perror("exec");
            std::exit(1);
        }

        // --- Parent ---
        close(to_child[0]);
        close(from_child[1]);

        reader_ptr = std::make_unique<InStream>(from_child[0]);
        writer_ptr = std::make_unique<OutStream>(to_child[1]);

        signal(SIGPIPE, SIG_IGN);
    }
};

using InStream = Interactor::InStream;
using OutStream = Interactor::OutStream;

} // namespace Solve