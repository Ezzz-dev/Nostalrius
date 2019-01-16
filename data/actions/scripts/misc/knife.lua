function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if target:getId() == 3594 then 
		target:transform(2977, 1)
		target:decay()
		return true
	end
	return false
end
