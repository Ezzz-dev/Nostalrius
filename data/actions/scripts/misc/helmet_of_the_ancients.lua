function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if target:getId() == 3030 then
		item:getPosition():sendMagicEffect(14)
		item:transform(3230, 1)
		item:decay()
		target:remove(1)
		return true
	end
	return false
end
