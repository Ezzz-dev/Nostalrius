function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if target:getId() == 2917 then
		item:transform(2978, 1)
		item:decay()
		target:remove()
		return true
	end
	return false
end
