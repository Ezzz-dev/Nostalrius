function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if target:getId() == 3652 then 
		player:sendCancelMessage(target:getType():getDescription() .. ".")
		return true
	elseif target:getId() == 3653 then
		target:transform(3651, 1)
		target:decay()
		Game.createItem(3605, 1, target:getPosition()) 
		return true
	end
	return doDestroyItem(target)
end
