#include <config.h>

#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "ls-icons.h"
#include "nerd-icons.h"

#define COLOR_AND_SIZE(x) x, sizeof x - 1

#ifdef NO_TRUE_COLOURS

//
// Use 256 colours
//
// You can use this script to get the corresponding numbers:
// https://github.com/eikenb/terminal-colors
//
// $./terminal-colors -n
//

# define COLOR(n) COLOR_AND_SIZE("\x1b[38;5;"#n"m")
# define ENDCOLOR ("\e[0m")

# define LIGHT_PINK COLOR(219)
# define LIGHT_BLUE COLOR(39)
# define LIGHT_SILVER COLOR(253)
# define LIGHT_GREEN COLOR(154)
# define LIGHT_CYAN COLOR(123)
# define LIGHT_RED COLOR(203)
# define LIGHT_ORANGE COLOR(209)
# define LIGHT_MAROON COLOR(137)
# define LIGHT_YELLOW COLOR(228)
# define LIGHT_PURPLE COLOR(177)
# define DARK_PINK COLOR(200)
# define DARK_BLUE COLOR(27)
# define DARK_SILVER COLOR(240)
# define DARK_GREEN COLOR(76)
# define DARK_CYAN COLOR(44)
# define DARK_RED COLOR(124)
# define DARK_ORANGE COLOR(166)
# define DARK_MAROON COLOR(94)
# define DARK_YELLOW COLOR(220)
# define DARK_PURPLE COLOR(93)
# define PINK COLOR(201)
# define BLUE COLOR(33)
# define SILVER COLOR(245)
# define GREEN COLOR(82)
# define CYAN COLOR(45)
# define RED COLOR(196)
# define ORANGE COLOR(208)
# define MAROON COLOR(130)
# define YELLOW COLOR(226)
# define PURPLE COLOR(165)

#else // !NO_TRUE_COLOURS

//
// Use 256*256*256 colours (16 millions colours)
//
// Example from hexadecimal numbers:
//
// Red: #FF3A20
// 0xFF = 255
// 0x3A = 58
// 0x20 = 32
//
// red: COLOR(255, 58, 32)
//

# define COLOR(r,g,b) COLOR_AND_SIZE("\x1b[38;2;"#r";"#g";"#b"m")
# define ENDCOLOR ("\x1b[0m")

# define LIGHT_PINK COLOR(244, 143, 177)
# define LIGHT_BLUE COLOR(144, 202, 249)
# define LIGHT_SILVER COLOR(189, 189, 189)
# define LIGHT_GREEN COLOR(105, 240, 174)
# define LIGHT_CYAN COLOR(24, 255, 255)
# define LIGHT_RED COLOR(255, 93, 72)
# define LIGHT_ORANGE COLOR(255, 171, 64)
# define LIGHT_MAROON COLOR(161, 136, 127)
# define LIGHT_YELLOW COLOR(255, 255, 141)
# define LIGHT_PURPLE COLOR(206, 147, 216)
# define DARK_PINK COLOR(173, 20, 87)
# define DARK_BLUE COLOR(21, 101, 192)
# define DARK_SILVER COLOR(117, 117, 117)
# define DARK_GREEN COLOR(0, 200, 83)
# define DARK_CYAN COLOR(0, 184, 212)
# define DARK_RED COLOR(209, 48, 27)
# define DARK_ORANGE COLOR(255, 109, 0)
# define DARK_MAROON COLOR(78, 52, 46)
# define DARK_YELLOW COLOR(255, 234, 0)
# define DARK_PURPLE COLOR(106, 27, 154)
# define PINK COLOR(233, 30, 99)
# define BLUE COLOR(33, 150, 243)
# define SILVER COLOR(158, 158, 158)
# define GREEN COLOR(0, 230, 118)
# define CYAN COLOR(0, 229, 255)
# define RED COLOR(255, 58, 32)
# define ORANGE COLOR(255, 145, 0)
# define MAROON COLOR(121, 85, 72)
# define YELLOW COLOR(255, 255, 0)
# define PURPLE COLOR(156, 39, 176)

#endif // NO_TRUE_COLOURS

typedef enum type_match {
  SUFFIX = 0b1,
  FULL = 0b10,
  PREFIX = 0b100
} e_type_match;

typedef struct {
  const char *string;
  size_t len;
  e_type_match type;
} t_match;

typedef struct {
  const char *icon;
  const t_match *matches;
  const char *color;
  size_t color_len;
} t_file_matching;

// http://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments
#define GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME

#define M1(t, x) (t_match) { x, sizeof x - 1, t }
#define M2(t, a, x) M1(t, a), M1(t, x)
#define M3(t, a, b, x) M2(t, a, b), M1(t, x)
#define M4(t, a, b, c, x) M3(t, a, b, c), M1(t, x)
#define M5(t, a, b, c, d, x) M4(t, a, b, c, d), M1(t, x)
#define M6(t, a, b, c, d, e, x) M5(t, a, b, c, d, e), M1(t, x)
#define M7(t, a, b, c, d, e, f, x) M6(t, a, b, c, d, e, f), M1(t, x)
#define M8(t, a, b, c, d, e, f, g, x) M7(t, a, b, c, d, e, f, g), M1(t, x)
#define M9(t, a, b, c, d, e, f, g, h, x) M8(t, a, b, c, d, e, f, g, h), M1(t, x)
#define M10(t, a, b, c, d, e, f, g, h, i, x) M9(t, a, b, c, d, e, f, g, h, i), M1(t, x)
#define M_(t, ...) GET_MACRO(__VA_ARGS__, M10, M9, M8, M7, M6, M5, M4, M3, M2, M1)(t, __VA_ARGS__)

// Matching is case insensitive.
#define P(...) M_(PREFIX, __VA_ARGS__) // Match prefix
#define S(...) M_(SUFFIX, __VA_ARGS__) // Match suffix
#define F(...) M_(FULL, __VA_ARGS__)   // Match full filename

#define END() (t_match) { 0 }
#define MATCH(...) (const t_match[]) { __VA_ARGS__ , END() }

// Icons are official Nerd Fonts glyph names, see src/nerd-icons.h and
// scripts/gen-nerd-icons.py: NF_SETI_PYTHON is the glyph "seti-python".
// The first entry that matches wins, so specific entries go first.
static const t_file_matching file_matches[] = {

  // Insert new data here, not at the end of the structure

  // ---- Full file names ----
  { NF_SETI_LICENSE, MATCH( F("LICENSE", "LICENCE", "COPYING", "COPYRIGHT",
                              "UNLICENSE"),
                            P("LICENSE.", "LICENSE-", "LICENCE.", "COPYING.") ), YELLOW},
  { NF_OCT_BOOK, MATCH( F("README"), P("README.", "README-") ), YELLOW},
  { NF_OCT_HISTORY, MATCH( F("CHANGELOG", "CHANGES", "HISTORY", "NEWS"),
                           P("CHANGELOG.", "CHANGES.", "HISTORY.", "NEWS.") ), BLUE},
  { NF_OCT_PEOPLE, MATCH( F("AUTHORS", "CONTRIBUTORS", "MAINTAINERS", "THANKS",
                            "CODEOWNERS"),
                          P("AUTHORS.", "CONTRIBUTORS.", "THANKS.", "THANKS-") ), LIGHT_BLUE},
  { NF_OCT_BOOK, MATCH( F("CONTRIBUTING", "CONTRIBUTE", "INSTALL", "HACKING",
                          "NOTICE", "MANIFEST", "BUGS", "PACKAGING"),
                        P("CONTRIBUTING.", "INSTALL.", "README_") ), DARK_BLUE},
  { NF_OCT_CHECKLIST, MATCH( F("TODO"), P("TODO.") ), YELLOW},
  { NF_SETI_MAKEFILE, MATCH( F("Makefile", "GNUmakefile", "Makefile.am",
                               "Makefile.in", "Kbuild"), S(".mk", ".mak") ), PINK},
  { NF_DEV_CMAKE, MATCH( F("CMakeLists.txt", "CMakeCache.txt"), S(".cmake") ), GREEN},
  { NF_SETI_BAZEL, MATCH( F("BUILD", "BUILD.bazel", "WORKSPACE", "MODULE.bazel"),
                          S(".bzl", ".bazel", ".bazelrc") ), GREEN},
  { NF_DEV_DOCKER, MATCH( F("Dockerfile", "Containerfile", "docker-compose.yml",
                            "docker-compose.yaml", "compose.yml", "compose.yaml",
                            ".dockerignore"),
                          P("Dockerfile.", "docker-compose."), S(".dockerfile") ), DARK_BLUE},
  { NF_DEV_VAGRANT, MATCH( F("Vagrantfile") ), BLUE},
  { NF_CUSTOM_VIM, MATCH( F(".vimrc", "vimrc", ".gvimrc", "_vimrc", ".viminfo"),
                          P("vimrc."), S(".vim") ), GREEN},
  { NF_DEV_GIT, MATCH( F(".gitignore", ".gitattributes", ".gitmodules",
                         ".gitconfig", ".gitkeep", ".mailmap", ".git-blame-ignore-revs",
                         "HEAD", "ORIG_HEAD", "FETCH_HEAD"),
                       F("packed-refs", "COMMIT_EDITMSG"), P(".git") ), DARK_ORANGE},
  { NF_SETI_EDITORCONFIG, MATCH( F(".editorconfig") ), SILVER},
  { NF_SETI_ESLINT, MATCH( P(".eslintrc", "eslint.config."), F(".eslintignore") ), PURPLE},
  { NF_CUSTOM_PRETTIER, MATCH( P(".prettierrc", "prettier.config."),
                               F(".prettierignore") ), CYAN},
  { NF_SETI_NPM, MATCH( F("package.json", "package-lock.json", ".npmrc",
                          ".npmignore") ), RED},
  { NF_SETI_YARN, MATCH( F("yarn.lock", ".yarnrc", ".yarnrc.yml") ), BLUE},
  { NF_SETI_TSCONFIG, MATCH( P("tsconfig.", "jsconfig.") ), BLUE},
  { NF_SETI_WEBPACK, MATCH( P("webpack.") ), BLUE},
  { NF_SETI_GULP, MATCH( P("gulpfile.") ), RED},
  { NF_SETI_GRUNT, MATCH( P("gruntfile.") ), YELLOW},
  { NF_SETI_BOWER, MATCH( F("bower.json", ".bowerrc", "Bowerfile") ), YELLOW},
  { NF_SETI_BABEL, MATCH( P(".babelrc", "babel.config."), F(".babelignore") ), YELLOW},
  { NF_DEV_RUST, MATCH( F("Cargo.toml", "Cargo.lock", "rust-toolchain",
                          "rust-toolchain.toml") ), LIGHT_MAROON},
  { NF_SETI_GO, MATCH( F("go.mod", "go.sum", "go.work") ), BLUE},
  { NF_DEV_PYTHON, MATCH( F("requirements.txt", "pyproject.toml", "setup.py",
                            "setup.cfg", "Pipfile", "Pipfile.lock", "poetry.lock",
                            "uv.lock", ".python-version"),
                          P("requirements-", "requirements_") ), YELLOW},
  { NF_DEV_RUBY, MATCH( F("Gemfile", "Gemfile.lock", "Rakefile", "Guardfile",
                          "Podfile", ".ruby-version", ".irbrc", ".gemrc", ".pryrc",
                          "config.ru") ), RED},
  { NF_SETI_GRADLE, MATCH( P("build.gradle", "settings.gradle"), F("gradlew") ), DARK_CYAN},
  { NF_SETI_MAVEN, MATCH( F("pom.xml") ), DARK_RED},
  { NF_DEV_NODEJS_SMALL, MATCH( F(".nvmrc", ".node-version") ), GREEN},
  { NF_DEV_PHP, MATCH( F("composer.json", "composer.lock"), P("Phakefile") ), PURPLE},
  { NF_SETI_ELIXIR, MATCH( F("mix.exs", "mix.lock") ), LIGHT_PURPLE},
  { NF_DEV_ERLANG, MATCH( F("rebar.config", "rebar.lock", "Emakefile") ), RED},
  { NF_MD_NIX, MATCH( F("flake.lock") ), LIGHT_BLUE},
  { NF_DEV_ROS, MATCH( F("package.xml", "CATKIN_IGNORE", "COLCON_IGNORE") ), DARK_BLUE},
  { NF_SETI_TEX, MATCH( F("latexmkrc", ".latexmkrc") ), DARK_GREEN},
  { NF_DEV_TERMINAL, MATCH( F(".bashrc", ".bash_profile", ".bash_login", ".bash_logout",
                              ".bash_aliases", ".bash_history", ".profile", ".zshrc",
                              ".zshenv", ".zprofile"),
                            F(".zlogin", ".zlogout", ".zsh_history", ".inputrc",
                              ".login", ".logout", ".xinitrc", ".xprofile",
                              ".Xresources", ".xsession") ), GREEN},
  { NF_DEV_TERMINAL, MATCH( F("configure", "config.guess", "config.sub",
                              "config.status", "config.rpath", "bootstrap",
                              "autogen.sh", "depcomp", "libtool", "compile"),
                            F("install-sh", "missing", "ltmain.sh") ), RED},
  { NF_OCT_TERMINAL, MATCH( F(".tmux.conf", "tmux.conf") ), GREEN},
  { NF_MD_KEY, MATCH( P("id_rsa", "id_ed25519", "id_ecdsa", "id_dsa"),
                      F("authorized_keys", "known_hosts", ".netrc", ".htpasswd") ), RED},
  { NF_OCT_FILE_BINARY, MATCH( F("a.out") ), DARK_GREEN},
  { NF_MD_LOCK, MATCH( S(".lock") ), MAROON},
  { NF_FA_TAG, MATCH( F("tags", "TAGS", "ctags", ".tags", "GTAGS", "GRTAGS",
                        "GPATH") ), LIGHT_YELLOW},
  { NF_FA_GEAR, MATCH( F(".env", ".envrc", ".flake8", ".pylintrc",
                         ".clang-format", ".clang-tidy", ".clangd",
                         "compile_commands.json", ".ls_colors", ".dir_colors"),
                       P(".env.") ), YELLOW},

  // ---- Compound suffixes ----
  { NF_MD_TEST_TUBE, MATCH( S(".test.js", ".spec.js", ".test.ts", ".spec.ts",
                              ".test.jsx", ".test.tsx", ".spec.jsx", ".spec.tsx") ), ORANGE},
  { NF_SETI_TYPESCRIPT, MATCH( S(".d.ts", ".d.mts", ".d.cts") ), DARK_BLUE},
  { NF_FA_FILE_ZIPPER, MATCH( S(".tar.gz", ".tar.xz", ".tar.bz2", ".tar.zst",
                                ".tar.lz", ".tar.lz4") ), DARK_RED},
  { NF_DEV_HTML5, MATCH( S(".html.erb") ), RED},
  { NF_DEV_COFFEESCRIPT, MATCH( S(".coffee.erb", ".coffee.ecr") ), MAROON},

  // ---- C / C++ / asm ----
  { NF_CUSTOM_C, MATCH( S(".c") ), BLUE},
  { NF_CUSTOM_C, MATCH( S(".h") ), PURPLE},
  { NF_CUSTOM_CPP, MATCH( S(".cpp", ".c++", ".cxx", ".cc", ".cp", ".ino",
                            ".ipp", ".tpp", ".inl") ), BLUE},
  { NF_CUSTOM_CPP, MATCH( S(".hpp", ".hh", ".hxx", ".h++") ), PURPLE},
  { NF_SETI_CU, MATCH( S(".cu", ".cuh") ), GREEN},
  { NF_CUSTOM_ASM, MATCH( S(".asm", ".s", ".nasm", ".masm", ".inc") ), LIGHT_BLUE},
  { NF_MD_LANGUAGE_CSHARP, MATCH( S(".cs", ".csx", ".csproj", ".sln") ), PURPLE},
  { NF_SETI_F_SHARP, MATCH( S(".fs", ".fsi", ".fsx", ".fsproj") ), CYAN},
  { NF_MD_LANGUAGE_FORTRAN, MATCH( S(".f", ".for", ".f77", ".f90", ".f95", ".f03",
                                     ".f08") ), PURPLE},

  // ---- Systems / compiled ----
  { NF_DEV_RUST, MATCH( S(".rs") ), MAROON},
  { NF_SETI_GO, MATCH( S(".go") ), BLUE},
  { NF_SETI_ZIG, MATCH( S(".zig", ".zon") ), ORANGE},
  { NF_SETI_NIM, MATCH( S(".nim", ".nims", ".nimble") ), YELLOW},
  { NF_SETI_CRYSTAL, MATCH( S(".cr") ), SILVER},
  { NF_SETI_D, MATCH( S(".d", ".di") ), RED},
  { NF_SETI_VALA, MATCH( S(".vala", ".vapi") ), PURPLE},
  { NF_CUSTOM_ADA, MATCH( S(".ada", ".adb", ".ads") ), DARK_GREEN},

  // ---- JVM ----
  { NF_DEV_JAVA, MATCH( S(".java", ".class") ), ORANGE},
  { NF_CUSTOM_KOTLIN, MATCH( S(".kt", ".kts") ), PURPLE},
  { NF_SETI_SCALA, MATCH( S(".scala", ".sc", ".sbt") ), RED},
  { NF_DEV_GROOVY, MATCH( S(".groovy", ".gradle", ".gvy") ), DARK_CYAN},
  { NF_SETI_CLOJURE, MATCH( S(".clj", ".cljs", ".cljc", ".cljx", ".cl2",
                              ".edn", ".hic") ), GREEN},
  { NF_FA_FILE_ZIPPER, MATCH( S(".jar", ".war", ".ear") ), DARK_PINK},

  // ---- Scripting ----
  { NF_DEV_PYTHON, MATCH( S(".py", ".pyw", ".pyi", ".py3", ".pyx", ".pxd",
                            ".ipy", ".gyp", ".gypi", ".tac") ), DARK_BLUE},
  { NF_DEV_JUPYTER, MATCH( S(".ipynb") ), ORANGE},
  { NF_DEV_RUBY, MATCH( S(".rb", ".ruby", ".erb", ".gemspec", ".rake", ".ru",
                          ".rbw", ".rbx", ".podspec", ".rabl") ), RED},
  { NF_DEV_PERL, MATCH( S(".pl", ".pm", ".pod", ".perl", ".plx", ".psgi",
                          ".t", ".xs") ), BLUE},
  { NF_DEV_PHP, MATCH( S(".php", ".phtml", ".php3", ".php4", ".php5", ".phps") ), PURPLE},
  { NF_SETI_LUA, MATCH( S(".lua", ".luau", ".rockspec") ), BLUE},
  { NF_SETI_R, MATCH( S(".r", ".rmd", ".rproj", ".rdata", ".rds") ), BLUE},
  { NF_SETI_JULIA, MATCH( S(".jl") ), PURPLE},
  { NF_DEV_DART, MATCH( S(".dart") ), CYAN},
  { NF_DEV_HASKELL, MATCH( S(".hs", ".lhs", ".hsc", ".c2hs", ".cabal") ), PURPLE},
  { NF_DEV_ERLANG, MATCH( S(".erl", ".hrl", ".beam", ".xrl", ".yrl",
                            ".app.src", ".escript") ), RED},
  { NF_SETI_ELIXIR, MATCH( S(".ex", ".exs", ".eex", ".heex", ".leex") ), PURPLE},
  { NF_SETI_ELM, MATCH( S(".elm") ), BLUE},
  { NF_SETI_OCAML, MATCH( S(".ml", ".mli", ".mll", ".mly") ), ORANGE},
  { NF_SETI_REASONML, MATCH( S(".re", ".rei") ), RED},
  { NF_SETI_RESCRIPT, MATCH( S(".res", ".resi") ), RED},
  { NF_SETI_PURESCRIPT, MATCH( S(".purs") ), SILVER},
  { NF_SETI_HAXE, MATCH( S(".hx", ".hxml") ), ORANGE},
  { NF_CUSTOM_SCHEME, MATCH( S(".scm", ".ss", ".rkt") ), RED},
  { NF_CUSTOM_COMMON_LISP, MATCH( S(".lisp", ".lsp", ".cl", ".fasl") ), SILVER},
  { NF_CUSTOM_FENNEL, MATCH( S(".fnl") ), YELLOW},
  { NF_CUSTOM_EMACS, MATCH( S(".el", ".elc", ".emacs", ".spacemacs") ), PURPLE},
  { NF_CUSTOM_ORGMODE, MATCH( S(".org") ), DARK_GREEN},

  // ---- Shell ----
  { NF_MD_FISH, MATCH( S(".fish") ), GREEN},
  { NF_SETI_POWERSHELL, MATCH( S(".ps1", ".psm1", ".psd1") ), BLUE},
  { NF_CUSTOM_MSDOS, MATCH( S(".bat", ".cmd") ), SILVER},
  { NF_DEV_TERMINAL, MATCH( S(".sh", ".bash", ".zsh", ".ksh", ".csh", ".tcsh",
                              ".bats", ".command", ".tool", ".install") ), GREEN},
  { NF_DEV_TERMINAL, MATCH( S(".zsh-theme", ".zwc") ), GREEN},

  // ---- Web ----
  { NF_DEV_JAVASCRIPT, MATCH( S(".js", ".mjs", ".cjs", "._js", ".es6", ".es") ), YELLOW},
  { NF_SETI_TYPESCRIPT, MATCH( S(".ts", ".mts", ".cts") ), BLUE},
  { NF_DEV_REACT, MATCH( S(".jsx", ".tsx") ), CYAN},
  { NF_SETI_VUE, MATCH( S(".vue") ), GREEN},
  { NF_SETI_SVELTE, MATCH( S(".svelte") ), ORANGE},
  { NF_CUSTOM_ASTRO, MATCH( S(".astro") ), ORANGE},
  { NF_DEV_COFFEESCRIPT, MATCH( S(".coffee", ".litcoffee", ".iced", ".cjsx") ), MAROON},
  { NF_DEV_HTML5, MATCH( S(".html", ".htm", ".xhtml") ), ORANGE},
  { NF_DEV_CSS3, MATCH( S(".css") ), BLUE},
  { NF_DEV_LESS, MATCH( S(".less") ), DARK_BLUE},
  { NF_DEV_SASS, MATCH( S(".scss", ".sass") ), PINK},
  { NF_DEV_STYLUS, MATCH( S(".styl", ".stylus") ), GREEN},
  { NF_SETI_HAML, MATCH( S(".haml", ".hamlc") ), YELLOW},
  { NF_SETI_PUG, MATCH( S(".pug", ".jade") ), DARK_MAROON},
  { NF_SETI_EJS, MATCH( S(".ejs") ), YELLOW},
  { NF_SETI_JINJA, MATCH( S(".jinja", ".jinja2", ".j2") ), MAROON},
  { NF_SETI_TWIG, MATCH( S(".twig") ), GREEN},
  { NF_SETI_LIQUID, MATCH( S(".liquid") ), GREEN},
  { NF_SETI_SLIM, MATCH( S(".slim") ), ORANGE},
  { NF_SETI_MUSTACHE, MATCH( S(".mustache", ".hbs", ".handlebars") ), ORANGE},
  { NF_SETI_GRAPHQL, MATCH( S(".graphql", ".gql") ), PINK},
  { NF_SETI_PRISMA, MATCH( S(".prisma") ), SILVER},
  { NF_SETI_WASM, MATCH( S(".wasm", ".wat") ), PURPLE},

  // ---- Data / config ----
  { NF_SETI_JSON, MATCH( S(".json", ".jsonc", ".json5", ".jsonl", ".ndjson",
                           ".cson", ".geojson", ".webmanifest") ), YELLOW},
  { NF_SETI_YML, MATCH( S(".yaml", ".yml") ), LIGHT_RED},
  { NF_CUSTOM_TOML, MATCH( S(".toml") ), SILVER},
  { NF_SETI_XML, MATCH( S(".xml", ".xsd", ".xsl", ".xslt", ".plist", ".launch",
                          ".urdf", ".xacro", ".sdf", ".qrc") ), ORANGE},
  { NF_SETI_CSV, MATCH( S(".csv", ".tsv", ".psv") ), GREEN},
  { NF_FA_GEAR, MATCH( S(".conf", ".config", ".cfg", ".ini", ".cnf", ".rc",
                         ".properties", ".desktop", ".directory", ".service") ), YELLOW},
  { NF_FA_GEAR, MATCH( S(".prefs", ".settings", ".timer", ".socket", ".target",
                         ".mount", ".rules", ".reg") ), YELLOW},
  { NF_DEV_SQLITE, MATCH( S(".sqlite", ".sqlite3", ".db", ".db3", ".s3db") ), BLUE},
  { NF_SETI_DB, MATCH( S(".sql", ".mdb", ".accdb", ".dump", ".pgsql", ".mysql") ), DARK_YELLOW},
  { NF_OCT_DATABASE, MATCH( S(".cache", ".parquet", ".feather", ".arrow", ".avro",
                              ".h5", ".hdf5", ".npy", ".npz", ".pkl") ), GREEN},
  { NF_OCT_DATABASE, MATCH( S(".pickle", ".mat", ".nc", ".lmdb", ".bag",
                              ".mcap", ".db3-wal", ".pcd", ".ply") ), GREEN},
  { NF_MD_PROTOCOL, MATCH( S(".proto", ".msg", ".srv", ".action", ".idl",
                             ".thrift", ".fbs", ".capnp") ), LIGHT_CYAN},
  { NF_DEV_QT, MATCH( S(".qml", ".ui", ".pro", ".pri") ), GREEN},
  { NF_SETI_TERRAFORM, MATCH( S(".tf", ".tfvars", ".tfstate", ".hcl") ), PURPLE},
  { NF_MD_NIX, MATCH( S(".nix") ), LIGHT_BLUE},
  { NF_OCT_DIFF, MATCH( S(".diff", ".patch", ".rej", ".orig") ), DARK_GREEN},

  // ---- Documents ----
  { NF_DEV_MARKDOWN, MATCH( S(".md", ".markdown", ".mdx", ".mkd") ), BLUE},
  { NF_SETI_TEX, MATCH( S(".tex", ".ltx", ".sty", ".cls", ".dtx", ".ins",
                          ".bib", ".bst", ".bbl", ".aux") ), DARK_GREEN},
  { NF_MD_BOOK_OPEN_VARIANT, MATCH( S(".rst", ".adoc", ".asciidoc", ".texi",
                                      ".texinfo", ".info", ".man", ".1", ".8") ), LIGHT_BLUE},
  { NF_FA_FILE_PDF, MATCH( S(".pdf") ), RED},
  { NF_MD_FILE_WORD, MATCH( S(".doc", ".docx", ".docm", ".odt", ".rtf") ), BLUE},
  { NF_MD_FILE_EXCEL, MATCH( S(".xls", ".xlsx", ".xlsm", ".ods") ), GREEN},
  { NF_MD_FILE_POWERPOINT, MATCH( S(".ppt", ".pptx", ".pps", ".ppsx", ".odp") ), ORANGE},
  { NF_FA_FILE_ZIPPER, MATCH( S(".epub", ".mobi", ".azw3") ), GREEN},
  { NF_OCT_LOG, MATCH( S(".log", ".journal", ".out") ), MAROON},
  { NF_MD_SUBTITLES, MATCH( S(".srt", ".ass", ".ssa", ".vtt", ".sub") ), PURPLE},
  { NF_MD_EMAIL, MATCH( S(".eml", ".mbox") ), LIGHT_BLUE},
  { NF_FA_FILE_LINES, MATCH( S(".txt", ".text", ".nfo") ), LIGHT_SILVER},

  // ---- Images ----
  { NF_MD_SVG, MATCH( S(".svg", ".svgz") ), DARK_YELLOW},
  { NF_SETI_PHOTOSHOP, MATCH( S(".psd", ".psb") ), BLUE},
  { NF_SETI_ILLUSTRATOR, MATCH( S(".ai", ".eps") ), ORANGE},
  { NF_MD_PALETTE, MATCH( S(".xcf", ".kra", ".blend", ".fig", ".sketch") ), LIGHT_PINK},
  { NF_FA_FILE_IMAGE, MATCH( S(".png", ".jpg", ".jpeg", ".jpe", ".gif", ".bmp",
                               ".webp", ".avif", ".heic", ".heif") ), ORANGE},
  { NF_FA_FILE_IMAGE, MATCH( S(".ico", ".icns", ".tif", ".tiff", ".tga", ".raw",
                               ".cr2", ".nef", ".dng", ".jxl") ), ORANGE},
  { NF_FA_FILE_IMAGE, MATCH( S(".ppm", ".pgm", ".pbm", ".pnm", ".exr", ".hdr",
                               ".xpm", ".xbm") ), ORANGE},
  { NF_MD_CUBE_OUTLINE, MATCH( S(".stl", ".obj", ".fbx", ".gltf", ".glb", ".dae",
                                 ".3ds", ".step", ".stp", ".dxf") ), LIGHT_PURPLE},

  // ---- Audio / Video ----
  { NF_FA_FILE_AUDIO, MATCH( S(".mp3", ".flac", ".wav", ".ogg", ".opus", ".m4a",
                               ".aac", ".wma", ".ape", ".alac") ), CYAN},
  { NF_FA_FILE_AUDIO, MATCH( S(".aiff", ".aif", ".mid", ".midi", ".ac3",
                               ".m4p", ".acc", ".amr") ), CYAN},
  { NF_FA_FILE_VIDEO, MATCH( S(".mp4", ".mkv", ".webm", ".mov", ".avi", ".flv",
                               ".wmv", ".m4v", ".mpg", ".mpeg") ), PURPLE},
  { NF_FA_FILE_VIDEO, MATCH( S(".3gp", ".3gpp", ".m2ts", ".mts", ".vob",
                               ".ogv", ".h264", ".h265", ".rmvb") ), PURPLE},

  // ---- Fonts ----
  { NF_FA_FONT, MATCH( S(".ttf", ".otf", ".ttc", ".woff", ".woff2", ".eot",
                         ".pcf", ".bdf", ".fon", ".psf") ), LIGHT_GREEN},

  // ---- Keys / certificates ----
  { NF_MD_CERTIFICATE, MATCH( S(".crt", ".cer", ".der", ".csr", ".p12", ".pfx",
                                ".p7b", ".crl") ), BLUE},
  { NF_MD_KEY, MATCH( S(".pem", ".key", ".pub", ".asc", ".gpg", ".sig", ".kdbx",
                        ".ovpn") ), YELLOW},

  // ---- Archives / packages ----
  { NF_LINUX_DEBIAN, MATCH( S(".deb", ".udeb", ".dsc") ), RED},
  { NF_LINUX_REDHAT, MATCH( S(".rpm", ".spec") ), RED},
  { NF_DEV_APPLE, MATCH( S(".dmg", ".pkg", ".app", ".ipa") ), SILVER},
  { NF_MD_ANDROID, MATCH( S(".apk", ".aab") ), GREEN},
  { NF_MD_MICROSOFT_WINDOWS, MATCH( S(".exe", ".msi", ".dll", ".com", ".sys",
                                      ".lnk") ), BLUE},
  { NF_MD_DISC, MATCH( S(".iso", ".img", ".vmdk", ".vdi", ".qcow2", ".vhd",
                         ".vhdx") ), LIGHT_BLUE},
  { NF_FA_FILE_ZIPPER, MATCH( S(".zip", ".tar", ".gz", ".tgz", ".xz", ".txz",
                                ".bz2", ".tbz2", ".zst", ".7z") ), DARK_RED},
  { NF_FA_FILE_ZIPPER, MATCH( S(".rar", ".lz", ".lz4", ".lzma", ".lzo", ".z",
                                ".cab", ".cpio", ".ar", ".zpaq") ), DARK_RED},
  { NF_FA_FILE_ZIPPER, MATCH( S(".whl", ".egg", ".gem", ".xpi", ".crx", ".nupkg",
                                ".snap", ".flatpak", ".appimage", ".nzb") ), LIGHT_ORANGE},

  // ---- Binary / object ----
  { NF_OCT_FILE_BINARY, MATCH( S(".o", ".ko", ".so", ".a",
                                             ".lib", ".elf", ".bin", ".hex") ), DARK_GREEN},
  { NF_OCT_FILE_BINARY, MATCH( S(".pyc", ".pyo", ".pyd", ".dylib", ".dat",
                                 ".pak", ".pdb", ".bsdiff", ".dex", ".onnx") ), DARK_PURPLE},
  { NF_OCT_FILE_BINARY, MATCH( S(".pt", ".pth", ".ckpt", ".safetensors", ".engine",
                                 ".tflite", ".pb", ".gguf", ".objdump", ".d-objdump") ), DARK_GREEN},
  { NF_FA_TAG, MATCH( S(".pid", ".ctags", ".tags", ".gemtags") ), ORANGE},
  { NF_MD_FILE_RESTORE, MATCH( S(".bak", ".backup", ".old", ".swp", ".swo", ".tmp",
                                 "~") ), DARK_SILVER},
  { NF_MD_FILE_CAD, MATCH( S(".dwg", ".sch", ".kicad_pcb", ".kicad_sch", ".brd") ), DARK_CYAN},

  // ---- Generic dotfiles ----
  { NF_FA_GEAR, MATCH( S("rc", "ignore") ), DARK_YELLOW},
  { NF_FA_FILE, MATCH( P(".") ), NULL, 0}
  // Insert new data at the beginning of the struture, not here !
};

// Directories with a special name. Other directories use NF_FA_FOLDER.
static const t_file_matching dir_matches[] = {
  { NF_CUSTOM_FOLDER_GIT, MATCH( F(".git") ), DARK_ORANGE},
  { NF_CUSTOM_FOLDER_GITHUB, MATCH( F(".github") ), BLUE},
  { NF_CUSTOM_FOLDER_NPM, MATCH( F("node_modules") ), RED},
  { NF_CUSTOM_FOLDER_CONFIG, MATCH( F(".config", "config", "etc", ".vscode",
                                      ".idea") ), BLUE},
  { NF_MD_FOLDER_KEY, MATCH( F(".ssh", ".gnupg", ".password-store") ), BLUE},
  { NF_MD_FOLDER_DOWNLOAD, MATCH( F("Downloads", "下载") ), BLUE},
  { NF_MD_FOLDER_TEXT, MATCH( F("Documents", "文档", "doc", "docs") ), BLUE},
  { NF_MD_FOLDER_IMAGE, MATCH( F("Pictures", "图片", "images", "img") ), BLUE},
  { NF_MD_FOLDER_MUSIC, MATCH( F("Music", "音乐") ), BLUE},
  { NF_MD_FOLDER_PLAY, MATCH( F("Videos", "视频", "Movies") ), BLUE},
  { NF_MD_DESKTOP_CLASSIC, MATCH( F("Desktop", "桌面") ), BLUE},
  { NF_MD_FOLDER_NETWORK, MATCH( F("Public", "公共的") ), BLUE},
  { NF_MD_FOLDER_COG, MATCH( F(".cache", ".local", "build", "install") ), BLUE},
  { NF_FA_FOLDER, MATCH( F(".", "..") ), DARK_BLUE},
};

static const size_t size_file_matches = sizeof file_matches / sizeof file_matches[0];
static const size_t size_dir_matches = sizeof dir_matches / sizeof dir_matches[0];

// Return 0 if filename and the expression correspond
static int match(const char *filename, size_t len, const t_match *match) {
  const e_type_match type = match->type;
  if (type & PREFIX) {
    return len < match->len ? -1 : strncasecmp(filename, match->string, match->len);
  }
  else if (type & SUFFIX) {
    return len < match->len ? -1 : strncasecmp(filename + len - match->len,
                                                match->string, match->len);
  }
  else { // if type & FULL
    return len != match->len ? -1 : strncasecmp(filename, match->string, len);
  }
}

static void write_icon(const char *icon, const char *color, size_t color_len, FILE *stream, int is_colored) {
  int insert_color = !is_colored && color;

  if (insert_color)
    fwrite(color, 1, color_len ,stream);

  fputs(icon, stream);

  if (insert_color)
    fwrite(ENDCOLOR, 1, sizeof ENDCOLOR - 1,stream);
}

static const t_file_matching *find(const t_file_matching *table, size_t size,
                                   const char *filename, size_t len) {
  for (size_t i = 0; i < size; i += 1) {
    for (size_t j = 0; table[i].matches[j].len; j++) {
      if (!match(filename, len, &table[i].matches[j]))
        return &table[i];
    }
  }
  return NULL;
}

static void _print_icon(const char *filename, const size_t len,
                        FILE *stream, enum ls_icon_kind kind,
                        int is_colored) {
  const t_file_matching *m;

  switch (kind) {
  case LS_ICON_LINK:
    write_icon(NF_COD_FILE_SYMLINK_FILE, LIGHT_BLUE, stream, is_colored);
    return;
  case LS_ICON_LINK_DIR:
    write_icon(NF_COD_FILE_SYMLINK_DIRECTORY, LIGHT_BLUE, stream, is_colored);
    return;
  case LS_ICON_LINK_BROKEN:
    write_icon(NF_MD_LINK_OFF, RED, stream, is_colored);
    return;
  case LS_ICON_DIR:
    m = find(dir_matches, size_dir_matches, filename, len);
    if (m)
      write_icon(m->icon, m->color, m->color_len, stream, is_colored);
    else
      write_icon(NF_FA_FOLDER, BLUE, stream, is_colored);
    return;
  case LS_ICON_FIFO:
    write_icon(NF_MD_PIPE, YELLOW, stream, is_colored);
    return;
  case LS_ICON_SOCK:
    write_icon(NF_MD_POWER_SOCKET, PURPLE, stream, is_colored);
    return;
  case LS_ICON_CHARDEV:
    write_icon(NF_MD_CHIP, YELLOW, stream, is_colored);
    return;
  case LS_ICON_BLOCKDEV:
    write_icon(NF_MD_HARDDISK, YELLOW, stream, is_colored);
    return;
  case LS_ICON_FILE:
  case LS_ICON_EXEC:
    break;
  }

  m = find(file_matches, size_file_matches, filename, len);
  if (m)
    write_icon(m->icon, m->color, m->color_len, stream, is_colored);
  else if (kind == LS_ICON_EXEC)
    write_icon(NF_MD_APPLICATION, GREEN, stream, is_colored);
  else
    write_icon(NF_FA_FILE, NULL, 0, stream, 0);
}

int print_icon(const char *filename, size_t len, FILE *stream,
               enum ls_icon_kind kind, int is_quoted, int is_colored) {
  if (is_quoted && len >= 2) {
    filename += 1;
    len -= 2;
  }
  _print_icon(filename, len, stream, kind, is_colored);
  fputc(' ', stream);
  return 0;
}

int print_arrow_right(FILE *stream) {
  fputs(" " NF_FA_ARROW_RIGHT " ", stream);
  return 0;
}
