function onUse(player, item, fromPosition, target, toPosition)
	if math.random(1, 100) <= 90 then
		item:getPosition():sendMagicEffect(3)
		return true
	else
		player:getPosition():sendMagicEffect(3)
	end
	return true
end
