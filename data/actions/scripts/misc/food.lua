function onUse(player, item, fromPosition, target, toPosition)
	local itemType = ItemType(item:getId())
	local condition = player:getCondition(CONDITION_REGENERATION, CONDITIONID_DEFAULT)
	if condition and math.floor(condition:getTicks() / 1000 + (itemType:getNutrition() * 12)) >= 1200 then
		player:sendTextMessage(MESSAGE_STATUS_SMALL, "You are full.")
	else
		player:feed(itemType:getNutrition() * 12)
		item:remove(1)
	end
	
	return true
end
