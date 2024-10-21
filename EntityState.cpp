#include "EntityState.h"

std::string EntityState::entityStateIDToString(EntityStateID state) {
	switch (state) {
	case EntityStateID::NO_STATE: return "NO_STATE";
	case EntityStateID::ACTIVATE: return "ACTIVATE";
	case EntityStateID::SPAWN: return "SPAWN";
	case EntityStateID::START: return "START";
	case EntityStateID::PAUSE: return "PAUSE";
	case EntityStateID::ATTACH: return "ATTACH";
	case EntityStateID::UNKNOWN_1: return "UNKNOWN_1";
	case EntityStateID::UNKNOWN_2: return "UNKNOWN_2";
	case EntityStateID::ENABLE: return "ENABLE";
	case EntityStateID::SIMULATE: return "SIMULATE";
	case EntityStateID::LOCK: return "LOCK";
	case EntityStateID::SHOW: return "SHOW";
	case EntityStateID::SUSPEND: return "SUSPEND";
	case EntityStateID::PROXY_ENABLE: return "PROXY_ENABLE";
	case EntityStateID::FLOATING: return "FLOATING";
	case EntityStateID::LIGHT_SWITCH_ON: return "LIGHT_SWITCH_ON";
	case EntityStateID::INSTALL_PROXY: return "INSTALL_PROXY";
	case EntityStateID::UNKNOWN_3: return "UNKNOWN_3";
	case EntityStateID::UNKNOWN_4: return "UNKNOWN_4";
	case EntityStateID::UNKNOWN_5: return "UNKNOWN_5";
	case EntityStateID::SUSPENDED: return "SUSPENDED";
	case EntityStateID::GHOSTED: return "GHOSTED";
	case EntityStateID::INVISIBLE: return "INVISIBLE";
	case EntityStateID::FROZEN: return "FROZEN";
	default: return "UNKNOWN_STATE";
	}
}

/// <summary>
/// Converts game entity state flags to human-readable text from the uint that they are contained within.
/// </summary>
/// <param name="state">Entity state</param>
/// <returns>States as a human-readable string.</returns>
std::string EntityState::DumpStatesToString(EntityState::EntityStateID state) {
	std::string output = "";

	if ((state & EntityStateID::NO_STATE) == EntityStateID::NO_STATE) {
		output += "NO_STATE,";
	} if ((state & EntityStateID::ACTIVATE) == EntityStateID::ACTIVATE) {
		output += "ACTIVATE,";
	} if ((state & EntityStateID::SPAWN) == EntityStateID::SPAWN) {
		output += "SPAWN,";
	} if ((state & EntityStateID::START) == EntityStateID::START) {
		output += "START,";
	} if ((state & EntityStateID::PAUSE) == EntityStateID::PAUSE) {
		output += "PAUSE,";
	} if ((state & EntityStateID::ATTACH) == EntityStateID::ATTACH) {
		output += "ATTACH,";
	} if ((state & EntityStateID::UNKNOWN_1) == EntityStateID::UNKNOWN_1) {
		output += "UNKNOWN_1,";
	} if ((state & EntityStateID::UNKNOWN_2) == EntityStateID::UNKNOWN_2) {
		output += "UNKNOWN_2,";
	} if ((state & EntityStateID::ENABLE) == EntityStateID::ENABLE) {
		output += "ENABLE,";
	} if ((state & EntityStateID::SIMULATE) == EntityStateID::SIMULATE) {
		output += "SIMULATE,";
	} if ((state & EntityStateID::LOCK) == EntityStateID::LOCK) {
		output += "LOCK,";
	} if ((state & EntityStateID::SHOW) == EntityStateID::SHOW) {
		output += "SHOW,";
	} if ((state & EntityStateID::SUSPEND) == EntityStateID::SUSPEND) {
		output += "SUSPEND,";
	} if ((state & EntityStateID::PROXY_ENABLE) == EntityStateID::PROXY_ENABLE) {
		output += "PROXY_ENABLE,";
	} if ((state & EntityStateID::FLOATING) == EntityStateID::FLOATING) {
		output += "FLOATING,";
	} if ((state & EntityStateID::LIGHT_SWITCH_ON) == EntityStateID::LIGHT_SWITCH_ON) {
		output += "LIGHT_SWITCH_ON,";
	} if ((state & EntityStateID::INSTALL_PROXY) == EntityStateID::INSTALL_PROXY) {
		output += "INSTALL_PROXY,";
	} if ((state & EntityStateID::UNKNOWN_3) == EntityStateID::UNKNOWN_3) {
		output += "UNKNOWN_3,";
	} if ((state & EntityStateID::UNKNOWN_4) == EntityStateID::UNKNOWN_4) {
		output += "UNKNOWN_4,";
	} if ((state & EntityStateID::UNKNOWN_5) == EntityStateID::UNKNOWN_5) {
		output += "UNKNOWN_5,";
	} if ((state & EntityStateID::SUSPENDED) == EntityStateID::SUSPENDED) {
		output += "SUSPENDED,";
	} if ((state & EntityStateID::GHOSTED) == EntityStateID::GHOSTED) {
		output += "GHOSTED,";
	} if ((state & EntityStateID::INVISIBLE) == EntityStateID::INVISIBLE) {
		output += "INVISIBLE,";
	} if ((state & EntityStateID::FROZEN) == EntityStateID::FROZEN) {
		output += "FROZEN,";
	}

	return output;
}

void __fastcall EntityState::h_state_change(EntityState::Data* _this, void* _EDX, int* param_1, int param_2, EntityStateID state, bool shouldAddState)
{
	//if (((_this->stateID & EntityStateID::ENABLE) == EntityStateID::ENABLE) && !shouldAddState) {
		//std::cout << "state_change - Overrode DISABLE to ENABLE!" << "\n";
	//}

	state_change(_this, param_1, param_2, state, shouldAddState);
	// Set the LOCK flag.
	//_this->state |= EntityStateID::LOCK;
	// Remove the ENABLE flag.
	//_this->state &= ~(EntityStateID::ENABLE);

	//std::cout << "state_change " << param_1 << " " << param_2 << " " << entityStateIDToString(param_3) << " " << shouldAddState << "" << "\n";
}
