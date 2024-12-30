# ┌──────────────┐     ┌─────────────┐    ┌─────────────┐    ┌────────────┐
# │ Requirements │     │ Use Case    │    │ Class/Func  │    │ PyTest     │
# │              ┼────►│             ┼───►│             ┼───►│            │
# │  *_req.yaml  │ ▲   │   *_uc.md   │ ▲  │  *_xform.py │ ▲  │ *_test.py  │
# └──────────────┘ │   └─────────────┘ │  └─────────────┘ │  └────────────┘
#                  │                   │                  │                
#               policy_uc.md     policy_python.md      policy_pytest.md     
#                                                             
############################################################################

# Variables
VENV_DIR = .venv
WORKFLOW_DIR = ai_sw_workflow
PYTHON = $(VENV_DIR)/bin/python
PIP = $(VENV_DIR)/bin/pip
MODEL = 'gpt-4o'
# MODEL = 'gpt-4o-mini'
# MODEL = 'o1-mini'
# MODEL = "gpt-3.5-turbo"
MAX_TOKENS = 8000
TEMPERATURE = 0.1
MAIN_SCRIPT = $(WORKFLOW_DIR)/ai_sw_workflow.py -m=$(MAX_TOKENS) -T=$(TEMPERATURE) --model=$(MODEL)

# Define source and destination suffixes
REQ_SUFFIX  = _req.yaml
PSEUDO_SUFFIX  = _pseudo.yaml
POLICY_DIR  = ./$(WORKFLOW_DIR)/policy
POLICY_PSEUDO=$(POLICY_DIR)/policy_pseudo.yaml

# Conditional variable to switch policies
POLICY_MODE = c++20
# POLICY_MODE = python3.8

ifeq ($(POLICY_MODE), python3.8)
CODE_SUFFIX   = _code.py
TEST_SUFFIX   = _test.py
POLICY_CODE = $(POLICY_DIR)/policy_python3.8.yaml
POLICY_TEST= $(POLICY_DIR)/policy_pytest.yaml

else ifeq ($(POLICY_MODE), c++20)
CODE_SUFFIX   = _code.cpp
TEST_SUFFIX   = _test.cpp
POLICY_CODE = $(POLICY_DIR)/policy_c++20.yaml
POLICY_TEST= $(POLICY_DIR)/policy_gtest.yaml
endif

# Find all source files in subdirectories with the specified postfixes
EXCLUDE_SOURCES = -path "./$(WORKFLOW_DIR)/*" -prune
SUBDIR_REQ_SOURCES = $(shell find . -mindepth 2 -type f -name "*$(REQ_SUFFIX)" -not \( $(EXCLUDE_SOURCES) \))
BASEDIR_REQ_SOURCES = $(shell find . -mindepth 1 -maxdepth 1 -type f -name "*$(REQ_SUFFIX)" -not \( $(EXCLUDE_SOURCES) \))

# Generate corresponding destination file names
SUBDIR_PSEUDO_DESTINATIONS = $(SUBDIR_REQ_SOURCES:$(REQ_SUFFIX)=$(PSEUDO_SUFFIX))
SUBDIR_PCODE_DESTINATIONS  = $(SUBDIR_REQ_SOURCES:$(REQ_SUFFIX)=$(CODE_SUFFIX))
SUBDIR_PTEST_DESTINATIONS  = $(SUBDIR_REQ_SOURCES:$(REQ_SUFFIX)=$(TEST_SUFFIX))

BASEDIR_PSEUDO_DESTINATIONS = $(BASEDIR_REQ_SOURCES:$(REQ_SUFFIX)=$(PSEUDO_SUFFIX))
BASEDIR_PCODE_DESTINATIONS  = $(BASEDIR_REQ_SOURCES:$(REQ_SUFFIX)=$(CODE_SUFFIX))
BASEDIR_PTEST_DESTINATIONS  = $(BASEDIR_REQ_SOURCES:$(REQ_SUFFIX)=$(TEST_SUFFIX))

# Combine all destinations
DESTINATIONS = $(SUBDIR_PCODE_DESTINATIONS) $(SUBDIR_PTEST_DESTINATIONS) $(SUBDIR_PSEUDO_DESTINATIONS) \
               $(BASEDIR_PCODE_DESTINATIONS) $(BASEDIR_PTEST_DESTINATIONS) $(BASEDIR_PSEUDO_DESTINATIONS)

.PRECIOUS: $(DESTINATIONS)
.PHONY:  setup template test clean help count_lines  subdirs base

all: subdirs base test count_lines

subdirs: $(SUBDIR_PSEUDO_DESTINATIONS) $(SUBDIR_PCODE_DESTINATIONS) $(SUBDIR_PTEST_DESTINATIONS)

base: subdirs $(BASEDIR_PSEUDO_DESTINATIONS) $(BASEDIR_PCODE_DESTINATIONS) $(BASEDIR_PTEST_DESTINATIONS)

test:
	@$(PYTHON) -m pytest --tb=line | grep -vE "^(platform|rootdir|plugins|collected)"
count_lines:
	@echo "Counting lines of Python code and YAML files..."
	@python_lines=$$(find . -type f -name "*_xform.py" ! -name "*_test.py" ! -path "*/__pycache__/*" ! -path "./.cache/*" ! -path "./.git/*" -exec wc -l {} + | awk '{total += $$1} END {print total}'); \
	test_lines=$$(find . -type f -name "*_test.py" ! -path "*/__pycache__/*" ! -path "./.cache/*" ! -path "./.git/*" -exec wc -l {} + | awk '{total += $$1} END {print total}'); \
	yaml_lines=$$(find . -type f -name "*.yaml" ! -path "./policy/*" ! -path "./.cache/*" ! -path "./.git/*" -exec wc -l {} + | awk '{total += $$1} END {print total}'); \	total_lines=$$(($$python_lines + $$test_lines + $$yaml_lines)); \
	total_lines=$$(($$python_lines + $$test_lines + $$yaml_lines)); \
	echo "TOTAL LINES: $$total_lines = Code: $$python_lines + Test: $$test_lines (YAML: $$yaml_lines)"

# Rule to generate _pseudo.md from _req.md
%$(PSEUDO_SUFFIX): %$(REQ_SUFFIX)
	@$(PYTHON) $(MAIN_SCRIPT) --source $< --dest $@  --xform pseudo --policy $(POLICY_PSEUDO) --code "n.a."

# Rule to generate _code.py from _pseudo.md
%$(CODE_SUFFIX): %$(PSEUDO_SUFFIX)
	@$(PYTHON) $(MAIN_SCRIPT) --source $< --dest $@  --xform code   --policy $(POLICY_CODE)  --code $@

# Rule to generate _test.py from _code.py
%$(TEST_SUFFIX): %$(CODE_SUFFIX) %$(REQ_SUFFIX)
	@$(PYTHON) $(MAIN_SCRIPT) --source $(word 2,$^) --dest $@  --xform test  --policy $(POLICY_TEST) --code $<    


template:
	@if [ "$(new_name)" = "" ]; then \
		echo "Error: Please provide a new_name variable. Example: make template new_name=my_template"; \
		exit 1; \
	fi
	cp -r ai_sw_workflow/template ./$(new_name)
	mv ./$(new_name)/template_req.yaml ./$(new_name)/$(new_name)_req.yaml

clean:
	find . -type d -name "__pycache__" -exec rm -rf {} +
	rm -rfv  $(DESTINATIONS)
	find . -type f -name ".prompt_*" -exec rm -f {} +
	find . -type d -name ".pytest_cache" -exec rm -rf {} +

# Display help message
help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  all       - Set up the environment and run the script if needed"
	@echo "  setup     - Create a virtual environment and install dependencies"
	@echo "  test      - runs the pytest"
	@echo "  clean     - Remove generated files and clean the environment"
	@echo "  template new_name=<desired_new_name>  - Copy ai_sw_workflow/template to ./<new_name> and rename template_req.yaml to <new_name>.yaml"	
	@echo "  help      - Display this help message"
