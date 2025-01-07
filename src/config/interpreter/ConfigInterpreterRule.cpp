#include "ConfigInterpreterRule.hpp"

#include "ToVector.hpp"
#include "Join.hpp"

#include "Colors.hpp"

#include <vector>
#include <string>
#include <ostream>
#include <iostream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigInterpreterRule::ConfigInterpreterRule(void)
{}

ConfigInterpreterRule::ConfigInterpreterRule(const ConfigInterpreterRule& other)
{
	context_ = other.context_;
	validBlocks_ = other.validBlocks_;
	validDirectives_ = other.validDirectives_;
}

ConfigInterpreterRule::    ConfigInterpreterRule(
	const char* context[],
	const char* validBlocks[],
	const char* validDirectives[]
) :
	context_(toVector(context)),
	validBlocks_(toVector(validBlocks)),
	validDirectives_(toVector(validDirectives))
{}

ConfigInterpreterRule::~ConfigInterpreterRule(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigInterpreterRule&	ConfigInterpreterRule::operator=(const ConfigInterpreterRule& rhs)
{
	(void) rhs;
	return (*this);
}

std::ostream&	operator<<(std::ostream& os, const ConfigInterpreterRule& object)
{
	os << "--- Rule for context :" << C_YEL << join(object.getContext(), "->") << RESET << " ---" << std::endl;
	os << "  Valid blocks in context : " C_YEL << join(object.getValidBlocks(), ", ") << RESET << std::endl;
	os << "  Valid directives in context : " C_YEL << join(object.getValidDirectives(), ", ") << RESET;
	return (os);
}

// =============================================================================
// Setters and Getters
// =============================================================================

const std::vector<std::string>&	ConfigInterpreterRule::getContext(void) const
{
	return (context_);
}

const std::vector<std::string>&	ConfigInterpreterRule::getValidBlocks(void) const
{
	return (validBlocks_);
}

const std::vector<std::string>&	ConfigInterpreterRule::getValidDirectives(void) const
{
	return (validDirectives_);
}

// =============================================================================
// Public Methods
// =============================================================================

bool	ConfigInterpreterRule::isValidBlock(std::string block) const
{
	for (size_t i = 0; i != validBlocks_.size(); ++i)
	{
		if (validBlocks_[i] == block)
			return (true);
	}
	return (false);
}

bool	ConfigInterpreterRule::isValidDirective(std::string block) const
{
	for (size_t i = 0; i != validDirectives_.size(); ++i)
	{
		if (validDirectives_[i] == block)
			return (true);
	}
	return (false);
}