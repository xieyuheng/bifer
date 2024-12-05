#include "index.h"

commander_t *
commander_new(const char *name, const char *version, int argc, char **argv) {
    commander_t *self = new(commander_t);
    self->name = name;
    self->version = version;
    self->argc = argc;
    self->argv = argv;
    self->command_list = list_new_with((destructor_t *) command_destroy);
    return self;
}

void
commander_destroy(commander_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        commander_t *self = *self_pointer;
        list_destroy(&self->command_list);
        free(self);
        *self_pointer = NULL;
    }
}

const char *
commander_version(const commander_t *self) {
    return self->version;
}

void
commander_add(const commander_t *self, command_t *command) {
    list_push(self->command_list, command);
}

void
commander_use(const commander_t *self, commander_plugin_t *plugin) {
    (*plugin)(self);
}

static const command_t *
commander_default_command(const commander_t *self) {
    command_t *command = list_start(self->command_list);
    while (command) {
        if (strcmp(command->name, "default") == 0)
            return command;

        command = list_next(self->command_list);
    }

    return NULL;
}

void
commander_help(const commander_t *self) {
    printf("%s %s\n", self->name, self->version);
    printf("\n");

    printf("commands:\n");
    command_t *command = list_start(self->command_list);
    while (command) {
        printf("  %s", command->name);
        if (command->description)
            printf(" -- %s", command->description);
        printf("\n");
        command = list_next(self->command_list);
    }
}

static int
commander_run_command(const commander_t *self, const command_t *command) {
    assert(command);

    char **args = self->argv + 1;
    if (command->run)
        return (*command->run)(args, self);

    printf("no callback function in command: %s\n", command->name);
    return 1;
}

int
commander_run(const commander_t *self) {
    char *name = self->argv[1];

    if (!name) {
        const command_t *default_command = commander_default_command(self);
        if (default_command) {
            return commander_run_command(self, default_command);
        } else {
            commander_help(self);
            return 0;
        }
    }

    command_t *command = list_start(self->command_list);
    while (command) {
        if (strcmp(command->name, name) == 0)
            return commander_run_command(self, command);
        command = list_next(self->command_list);
    }

    printf("[commander_run] command not found: %s\n", name);
    return 1;
}
