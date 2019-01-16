function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if target:getId() == 3696 then 
		target:transform(3695, 1)
		target:decay()
		return true
	elseif target:getId() == 3702 then
		target:transform(3701, 1)
		target:decay()
		return true
	elseif target:getId() == 2130 then 
		target:remove()
		return true
	end
	return false
end
