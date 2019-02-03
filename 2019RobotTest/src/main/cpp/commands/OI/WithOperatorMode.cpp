#include "commands/OI/WithOperatorMode.h"
#include "Robot.h"

WithOperatorMode::WithOperatorMode(Command* climberMode, Command* elevatorMode):
    ConditionalCommand("WithOperatorMode", climberMode, elevatorMode)
{
}

bool WithOperatorMode::Condition() {
    return Robot::oi.climber_switch;
}