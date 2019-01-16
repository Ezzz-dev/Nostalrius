function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2566 then
		item:transform(2567, 1)
		item:decay()
	elseif item:getId() == 2567 then
		player:sendCancelMessage("It doesn't move.")
	elseif item:getId() == 2569 then
		item:transform(2570, 1)
		item:decay()
	elseif item:getId() == 2570 then
		item:transform(2569, 1)
		item:decay()
	end
	return true
end
