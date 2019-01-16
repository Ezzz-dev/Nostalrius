local condition = Condition(CONDITION_POISON)
condition:setTiming(1000)

function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then
		creature:addCondition(condition)
		creature:getPlayer():setStorageValue(270,1)
		Game.sendMagicEffect({x = 33362, y = 32811, z = 14}, 9)
	end
end
