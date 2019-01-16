function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if target:getId() == 4992 and player:getStorageValue(304) == 1 then 
		target:getPosition():sendMagicEffect(17)
		item:transform(4865, 1)
		item:decay()
		target:remove()
	elseif target:getId() == 4993 and player:getStorageValue(304) == 3 then 
		target:getPosition():sendMagicEffect(17)
		item:transform(4866, 1)
		item:decay()
		target:remove()
	elseif target:getId() == 4991 and player:getStorageValue(304) == 5 then
		target:getPosition():sendMagicEffect(17)
		item:transform(4864, 1)
		item:decay()
		target:remove()
	elseif target:getId() == 5013 and player:getStorageValue(304) == 5 then
		target:getPosition():sendMagicEffect(17)
		item:transform(5089, 1)
		item:decay()
		target:remove()
	end
	return false
end
