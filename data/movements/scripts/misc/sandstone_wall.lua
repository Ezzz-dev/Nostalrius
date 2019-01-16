function onStepIn(creature, item, fromPosition, toPosition)
	if item:getId() == 478 then
		item:transform(479, 1)
		item:decay()
	elseif item:getId() == 480 then
		item:transform(481, 1)
		item:decay()
	end
end

function onStepOut(creature, item, fromPosition, toPosition)
	if item:getId() == 479 then
		item:transform(478, 1)
		item:decay()
	elseif item:getId() == 481 then
		item:transform(480, 1)
		item:decay()
	end
end

function onAddItem(item, tileitem, position)
	if tileitem:getId() == 478 then
		tileitem:transform(479, 1)
		tileitem:decay()
	elseif tileitem:getId() == 480 then
		tileitem:transform(481, 1)
		tileitem:decay()
	end
end

function onRemoveItem(item, tileitem, position)
	if tileitem:getId() == 479 then
		tileitem:transform(478, 1)
		tileitem:decay()
	elseif tileitem:getId() == 481 then
		tileitem:transform(480, 1)
		tileitem:decay()
	end
end