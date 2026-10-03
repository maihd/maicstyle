# List of things todos
- Practice templates: oneshot program to write in 30 minutes - 1 hour, and remove after that. This is required one simple runtime or atleast library.

- Advanced coding techniques:
    - Code path flow
    - Error handling

- More examples:
    - Hash table
    - Data structures

- Complete exercises
- Create tools to demonstrate the ideas that worked
- API design guidelines, which is the best of how programming style should help

- Linked List vs Array performance benchmarks
    - Deep dive into implemenetation
    - Suggested usecases
    - Conclusion:
        - No data structure are silver bullet
        - No perfection in real life software, and array is good enough data structure for common cases

- New journey:
    - C/C++ as firmware/framework level for bindings even using Odin for system programming
    ```mermaid
    [OS] -> [OS SDK] -> [C/C++ Libraries] -> [C/C++ Framework/Core] -> [Odin/Other languages (optional)]
                                                                    -> [Scripting Language (optional)]
    ```
    - In the last layer (we called its high-level layer), if they are compiled languages, they should compiled as freestanding, its mean they are only depends on [C/C++ Framework/Core]
    - This architecture is for serious cross-platform production software (game)