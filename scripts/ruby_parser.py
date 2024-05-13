class ParseException(Exception):
    pass


class Parser:
    def __init__(self, src: list):
        self._src = src
        self._parse_index = 0
        self._results = { "dll" : True, "pg": False }
        self._help_called = False


    def parse(self) -> (dict | None):
        while self._parse_index < len(self._src):
            if self._src[self._parse_index][0] != '-':
                raise ParseException(f"Flag must begin from '-' sign.\n-> {self._src[self._parse_index]}")
            
            try:
                self.__check_flag()
                if self._help_called:
                    return None

                self.__try_to_extract_argument()
            except ParseException as err:
                raise err
        
        return self._results

    def __try_to_extract_argument(self) -> None:
        index = self._parse_index + 1
        if index > len(self._src):
            return
        
        token = self._src[index].lower()
        if token != "true" and token != "false":
            raise ParseException(f"Only \"true\" or \"false\" parameters are valid(in any register).\n-> {self._src[index]}")

        key = self._src[index - 1][1:]
        value = True if token == "true" else False
        
        self._results[key] = value
        self._parse_index = index + 1


    def __check_flag(self) -> None:
        flag = self._src[self._parse_index][1:]
        if flag not in ["dll", "pg", "help"]:
            raise ParseException(f"Wrong flag -> {flag}.\nType \"-help\" to get list of all flags")
        
        if flag == "help":
            self.__print_help()
            self._help_called = True

    def __print_help(self) -> None:
        print("Commands syntax:\n" 
              "     -<flag> <argument>\n" 
              "For example:\n"
              "     -dll true\n" 
              "Arguments can be in any case.\n" 
              "\n"
              "Available  flags:\n" 
              "     1) -dll : accepts \"true\" or \"false\" and responsible for building the engine dll;\n"
              "     2) -pg  : also accepts only \"true\" or \"false\". Responsible for building demo game. See playground\\src.")
        