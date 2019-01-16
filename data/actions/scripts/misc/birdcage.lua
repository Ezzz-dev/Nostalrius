function onUse(player, item, fromPosition, target, toPosition)
	if math.random(1, 100) <= 1 and math.random(1, 100) <= 10 then
		item:transform(2975, 0)
		item:decay()
	else
		item:getPosition():sendMagicEffect(22)
	end
	return true
end
