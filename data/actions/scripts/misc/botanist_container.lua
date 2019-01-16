function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if target:getId() == 3874 and player:getStorageValue(305) == 1 then
		item:transform(4868, 1)
		target:getPosition():sendMagicEffect(10)
		return true
	elseif target:getId() == 3885 and player:getStorageValue(305) == 3 then
		item:transform(4870, 1)
		target:getPosition():sendMagicEffect(10)
		return true
	elseif target:getId() == 3878 and player:getStorageValue(305) == 5 then 
		item:transform(4869, 1)
		target:getPosition():sendMagicEffect(10)
		return true
	end
	return false
end
